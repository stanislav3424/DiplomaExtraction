// Fill out your copyright notice in the Description page of Project Settings.

#include "UW_Inventory.h"
#include "CharacterLogic.h"
#include "InventoryLogic.h"
#include "Row.h"
#include "MacroLibrary.h"
#include "ItemLogic.h"
#include "LogicLibrary.h"
#include "UW_Item.h"
#include "UserWidgetLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "UW_InventoryGrid.h"
#include "Components/SizeBox.h"
#include "Blueprint/DragDropOperation.h"

UUW_Inventory::UUW_Inventory()
{
    bIsAutoInitializeChildLogic = false;
}

void UUW_Inventory::LogicChanged(ULogicBase* OldLogic, ULogicBase* NewLogic)
{
    Super::LogicChanged(OldLogic, NewLogic);

    if (auto InventoryLogic = Cast<UInventoryLogic>(OldLogic))
        InventoryLogic->OnInventoryChanged.RemoveDynamic(this, &UUW_Inventory::OnInventoryChanged);
    if (auto InventoryLogic = Cast<UInventoryLogic>(NewLogic))
        InventoryLogic->OnInventoryChanged.AddUniqueDynamic(this, &UUW_Inventory::OnInventoryChanged);

    if (auto InventoryLogic = Cast<UInventoryLogic>(NewLogic))
    {
        auto InventorySize  = InventoryLogic->GetInventorySize();
        auto SizeInViewport = UUserWidgetLibrary::GetSizeInViewport(InventorySize);
        SizeBox->SetWidthOverride(SizeInViewport.X);
        SizeBox->SetHeightOverride(SizeInViewport.Y);
    }

    ULogicLibrary::SetLogic(InventoryGrid, NewLogic);
    OnInventoryChanged();
}

bool UUW_Inventory::NativeOnDrop(
    const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    SetGridPreviewEnabled(false);

    if (!InOperation)
        return false;
    auto InventoryLogic = Cast<UInventoryLogic>(GetLogic_Implementation());
    if (!InventoryLogic)
        return false;
    auto Payload = Cast<ULogicBase>(InOperation->Payload);
    if (!Payload)
        return false;
    FIntVector2 FinalPosition =
        GetAdjustedPositionForItem(InGeometry, InDragDropEvent.GetScreenSpacePosition(), Payload);
    return InventoryLogic->AddItemToPosition(Payload, FinalPosition, false);
}

void UUW_Inventory::NativeOnDragEnter(
    const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    if (!InOperation)
        return ;
    auto InventoryLogic = Cast<UInventoryLogic>(GetLogic_Implementation());
    if (!InventoryLogic)
        return ;
    if (auto Payload = Cast<ULogicBase>(InOperation->Payload))
    {
        SetGridPreviewEnabled(true);
    }
}

bool UUW_Inventory::NativeOnDragOver(
    const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    if (!InOperation)
        return false;
    auto InventoryLogic = Cast<UInventoryLogic>(GetLogic_Implementation());
    if (!InventoryLogic)
        return false;
    if (auto Payload = Cast<ULogicBase>(InOperation->Payload))
    {
        UpdateGridPreviewPosition(InGeometry, InDragDropEvent.GetScreenSpacePosition(), Payload);
        return true;
    }

    return false;
}

void UUW_Inventory::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    if (!InOperation)
        return;
    SetGridPreviewEnabled(false);
}

void UUW_Inventory::OnInventoryChanged()
{
    if (!CanvasPanel)
        return;

    CHECK_FIELD_RETURN(ItemWidgetClass)

    for (auto Widget : ItemWidgets)
    {
        Widget->RemoveFromParent();
        Widget = nullptr;
    }

    auto InventoryLogic = Cast<UInventoryLogic>(GetLogic_Implementation());
    SetVisibility(InventoryLogic ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    if (!InventoryLogic)
        return;

    auto  ItemsInInventory = InventoryLogic->GetItemsInInventory().Array();
    int32 SizeInventory    = ItemsInInventory.Num();
    if (ItemWidgets.Num() != SizeInventory)
        ItemWidgets.SetNum(SizeInventory);

    for (int32 Index = 0; Index < SizeInventory; ++Index)
    {
        ItemWidgets[Index] = CreateWidget<UUW_Item>(GetOwningPlayer(), ItemWidgetClass);
        ULogicLibrary::SetLogic(ItemWidgets[Index], ItemsInInventory[Index].Key);

        ItemWidgets[Index]->SetAutoSize();

        auto PositionInViewport = UUserWidgetLibrary::GetPositionInViewport(ItemsInInventory[Index].Value.PositionItem);

        if (auto CanvasPanelSlot = CanvasPanel->AddChildToCanvas(ItemWidgets[Index]))
        {
            CanvasPanelSlot->SetPosition(PositionInViewport);
            CanvasPanelSlot->SetAutoSize(true);
        }
        
    }
}

void UUW_Inventory::SetGridPreviewEnabled(bool bEnabled)
{
    if (!GridPreviewImage)
    {
        GridPreviewImage = NewObject<UImage>(CanvasPanel);
        if (!GridPreviewImage || !CanvasPanel)
            return;

        CHECK_FIELD(GridPreviewMaterial);

        CanvasPanel->AddChild(GridPreviewImage);
        if (GridPreviewMaterial)
            GridPreviewImage->SetBrushFromMaterial(GridPreviewMaterial);

        GridPreviewImage->SetVisibility(ESlateVisibility::Hidden);
    }

    if (bEnabled)
        GridPreviewImage->SetVisibility(ESlateVisibility::HitTestInvisible);
    else
        GridPreviewImage->SetVisibility(ESlateVisibility::Hidden);
}

void UUW_Inventory::UpdateGridPreviewPosition(
    const FGeometry& InGeometry, const FVector2D& MousePosition, ULogicBase* Item)
{
    if (!Item || !GridPreviewImage)
        return;
    auto ItemLogicComponent = Item->GetLogicComponent<UItemLogic>();
    if (!ItemLogicComponent)
        return;

    auto InventoryLogic = Cast<UInventoryLogic>(GetLogic_Implementation());
    if (!InventoryLogic)
        return;
    FIntVector2 FinalPosition = GetAdjustedPositionForItem(InGeometry, MousePosition, Item);
    bool        bCanPlace     = InventoryLogic->CanAddItemToPosition(Item, FinalPosition, false);

    float       CellSize        = UUserWidgetLibrary::GetCellSize();
    FIntVector2 ItemSize        = ItemLogicComponent->GetItemSize();
    FVector2D   PreviewSize     = FVector2D(ItemSize.X * CellSize, ItemSize.Y * CellSize);
    FVector2D   PreviewPosition = UUserWidgetLibrary::GetSizeInViewport(FinalPosition);

    if (auto DynamicMaterial = GridPreviewImage->GetDynamicMaterial())
        DynamicMaterial->SetScalarParameterValue(PreviewOverlayParameterName, bCanPlace ? 1.0f : 0.0f);

    if (auto CanvasPanelSlot = Cast<UCanvasPanelSlot>(GridPreviewImage->Slot))
    {
        CanvasPanelSlot->SetPosition(PreviewPosition);
        CanvasPanelSlot->SetSize(PreviewSize);
    }
}

FIntVector2 UUW_Inventory::GetAdjustedPositionForItem(
    const FGeometry& InGeometry, const FVector2D& MousePosition, ULogicBase* Item) const
{
    auto ResultPosition = FIntVector2::ZeroValue;
    if (!Item)
        return ResultPosition;

    auto ItemLogicComponent = Item->GetLogicComponent<UItemLogic>();
    if (!ItemLogicComponent)
        return ResultPosition;

    const float CellSize         = UUserWidgetLibrary::GetCellSize();
    auto        ItemSize         = ItemLogicComponent->GetItemSize();
    FVector2D   ItemCenterOffset = FVector2D(ItemSize.X * CellSize / 2.0f, ItemSize.Y * CellSize / 2.0f);

    FVector2D LocalMousePosition = InGeometry.AbsoluteToLocal(MousePosition);
    FVector2D AdjustedPosition   = LocalMousePosition - ItemCenterOffset;

    int32 AdjustedX = FMath::Max(0, FMath::FloorToInt((AdjustedPosition.X + 0.5f * CellSize) / CellSize));
    int32 AdjustedY = FMath::Max(0, FMath::FloorToInt((AdjustedPosition.Y + 0.5f * CellSize) / CellSize));

    ResultPosition = FIntVector2(AdjustedX, AdjustedY);

    return ResultPosition;
}
