// Fill out your copyright notice in the Description page of Project Settings.

#include "UW_InventoryAdapterWidget.h"
#include "CharacterLogic.h"
#include "InventoryLogic.h"
#include "Row.h"
#include "MacroLibrary.h"

UUW_InventoryAdapterWidget::UUW_InventoryAdapterWidget()
{
    bIsAutoInitializeChildLogic = false;
}

void UUW_InventoryAdapterWidget::LogicChanged(ULogicBase* OldLogic, ULogicBase* NewLogic)
{
    Super::LogicChanged(OldLogic, NewLogic);

    if (auto CharacterLogic = Cast<UCharacterLogic>(OldLogic))
        CharacterLogic->OnEquipmentChanged.RemoveDynamic(this, &UUW_InventoryAdapterWidget::OnEquipmentChanged);

    if (auto CharacterLogic = Cast<UCharacterLogic>(NewLogic))
        CharacterLogic->OnEquipmentChanged.AddUniqueDynamic(this, &UUW_InventoryAdapterWidget::OnEquipmentChanged);

    OnEquipmentChanged();
}

void UUW_InventoryAdapterWidget::OnEquipmentChanged()
{
    UInventoryLogic* NewInventoryLogic = nullptr;
    if (auto CharacterLogic = Cast<UCharacterLogic>(GetLogic_Implementation()))
        NewInventoryLogic = Cast<UInventoryLogic>(CharacterLogic->GetEquippedItem(EEquipmentSlot::Backpack));

    if (InventoryLogic != NewInventoryLogic)
    {
        InventoryLogic = NewInventoryLogic;
        InitializeChildLogic(InventoryLogic);
    }
}
