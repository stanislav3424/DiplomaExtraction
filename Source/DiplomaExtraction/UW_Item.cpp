// Fill out your copyright notice in the Description page of Project Settings.

#include "UW_Item.h"
#include "ItemLogic.h"
#include "MacroLibrary.h"
#include "LogicLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "ExfilPlayerController.h"
#include "Components/SizeBox.h"
#include "UserWidgetLibrary.h"

void UUW_Item::LogicChanged(ULogicBase* OldLogic, ULogicBase* NewLogic)
{
    auto ItemLogic = UItemLogic::GetItemLogicComponent(NewLogic);
    CHECK_FIELD_RETURN(ItemLogic);
}

FReply UUW_Item::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
    {
        FEventReply EventReply =
            UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
        return EventReply.NativeReply;
    }
    return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UUW_Item::NativeOnDragDetected(
    const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
    auto DragDropOperation = Cast<UDragDropOperation>(
        UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropOperation::StaticClass()));
    if (!DragDropOperation)
        return;

    auto DragVisual = CreateWidget<UUW_Item>(GetOwningPlayer(), this->GetClass());
    if (!DragVisual)
        return;
    ULogicLibrary::SetLogic(DragVisual, GetLogic_Implementation());
    DragVisual->SetAutoSize();
    DragDropOperation->DefaultDragVisual = DragVisual;
    DragDropOperation->Pivot             = EDragPivot::CenterCenter;
    DragDropOperation->Payload           = GetLogic_Implementation();
    OutOperation                         = DragDropOperation;
}

void UUW_Item::SwitchRotation()
{
    SetRotation(!bIsRotated);
}

void UUW_Item::SetDragSettings()
{
    SetAutoSize();
    auto PC = GetOwningPlayer<AExfilPlayerController>();
    PC->OnInventoryItemRotate.AddUniqueDynamic(this, &UUW_Item::SwitchRotation);
}

void UUW_Item::SetRotation(bool bRotated)
{
    bIsRotated = bRotated;
}

void UUW_Item::SetAutoSize()
{
    if (auto ItemLogic = UItemLogic::GetItemLogicComponent(GetLogic_Implementation()))
    {
        auto ItemSize       = UItemLogic::GetRotationSize(ItemLogic->GetItemSize(), bIsRotated);
        auto SizeInViewport = UUserWidgetLibrary::GetSizeInViewport(ItemSize);
        SetSizeBoxSize(SizeInViewport.X, SizeInViewport.Y);
    }
}

void UUW_Item::SetSizeBoxSize(float Width, float Height)
{
    if (!SizeBox)
        return;
    SizeBox->SetWidthOverride(Width);
    SizeBox->SetHeightOverride(Height);
}

void UUW_Item::ClearSizeBoxSize()
{
    if (!SizeBox)
        return;
    SizeBox->ClearWidthOverride();
    SizeBox->ClearHeightOverride();
}