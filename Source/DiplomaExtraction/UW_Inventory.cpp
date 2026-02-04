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
#include "UW_InventoryGrid.h"
#include "Components/SizeBox.h"

UUW_Inventory::UUW_Inventory()
{
    bIsAutoInitializeChildLogic = false;
}

void UUW_Inventory::LogicChanged(ULogicBase* OldLogic, ULogicBase* NewLogic)
{
    Super::LogicChanged(OldLogic, NewLogic);

    CHECK_FIELD_RETURN(ItemWidgetClass);

    if (auto CharacterLogic = Cast<UCharacterLogic>(OldLogic))
        if (auto InventoryLogic = Cast<UInventoryLogic>(CharacterLogic->GetEquippedItem(EEquipmentSlot::Backpack)))
        {
            InventoryLogic->OnInventoryChanged.RemoveDynamic(this, &UUW_Inventory::OnInventoryChanged);
            OnInventoryChanged();
        }

    if (auto CharacterLogic = Cast<UCharacterLogic>(NewLogic))
        if (auto InventoryLogic = Cast<UInventoryLogic>(CharacterLogic->GetEquippedItem(EEquipmentSlot::Backpack)))
        {
            InventoryLogic->OnInventoryChanged.AddUniqueDynamic(this, &UUW_Inventory::OnInventoryChanged);
            InventoryLogic->OnInventoryChanged.Broadcast();
            ULogicLibrary::SetLogic(InventoryGrid, InventoryLogic);
            
            auto InventorySize = InventoryLogic->GetInventorySize();
            auto SizeInViewport = UUserWidgetLibrary::GetSizeInViewport(InventorySize);
            SizeBox->SetWidthOverride(SizeInViewport.X);
            SizeBox->SetHeightOverride(SizeInViewport.Y);
        }
}

void UUW_Inventory::OnInventoryChanged()
{
    if (!ItemWidgetClass || !CanvasPanel)
        return;

    for (auto Widget : ItemWidgets)
    {
        Widget->RemoveFromParent();
        Widget = nullptr;
    }

    auto CharacterLogic = Cast<UCharacterLogic>(GetLogic_Implementation());
    if (!CharacterLogic)
        return;
    auto InventoryLogic = Cast<UInventoryLogic>(CharacterLogic->GetEquippedItem(EEquipmentSlot::Backpack));
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

