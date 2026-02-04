// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterLogic.h"
#include "SpawnLibrary.h"
#include "EquipmentLogic.h"
#include "MacroLibrary.h"
#include "Row.h"

void UCharacterLogic::InitializeRowHandler(FDataTableRowHandle const& InitRowHandle)
{
    Super::InitializeRowHandler(InitRowHandle);

    auto Row = InitRowHandle.GetRow<FCharacterLogicRow>(FILE_FUNC);
    if (!Row)
        return;
}

bool UCharacterLogic::EquipItem(ULogicBase* Item)
{
    if (!IsValidEquippedItem(Item))
        return false;

    auto ItemSlot = GetEquipmentSlot(Item);

    return EquipItem(ItemSlot, Item);
}

bool UCharacterLogic::EquipItem(EEquipmentSlot const& TargetSlot, ULogicBase* Item)
{
    if (!IsValidEquippedItem(Item))
        return false;

    if (!CanEquipItem(TargetSlot, Item))
        return false;

    EquippedItems.Add(TargetSlot, Item);
    AddLogicComponent(Item);
    OnEquipmentChanged.Broadcast();

    return true;
}

bool UCharacterLogic::CanEquipItem(EEquipmentSlot const& TargetSlot, ULogicBase* Item)
{
    if (!IsValidEquippedItem(Item))
        return false;

    auto ItemSlot = GetEquipmentSlot(Item);
    if (ItemSlot != TargetSlot)
        return false;

    return !EquippedItems.Contains(TargetSlot);
}

ULogicBase* UCharacterLogic::UnequipItem(EEquipmentSlot const& TargetSlot)
{
    if (!EquippedItems.Contains(TargetSlot))
        return nullptr;

    auto Item = EquippedItems[TargetSlot];
    EquippedItems.Remove(TargetSlot);
    RemoveLogicComponent(Item);
    OnEquipmentChanged.Broadcast();

    return Item;
}

ULogicBase* UCharacterLogic::GetEquippedItem(EEquipmentSlot const& TargetSlot) const
{
    if (!EquippedItems.Contains(TargetSlot))
        return nullptr;

    auto Item = EquippedItems[TargetSlot];

    return Item;
}

bool UCharacterLogic::IsValidEquippedItem(ULogicBase* Item)
{
    if (!Item)
        return false;

    if (GetEquipmentSlot(Item) == EEquipmentSlot::None)
        return false;

    return true;
}


EEquipmentSlot UCharacterLogic::GetEquipmentSlot(ULogicBase* Item)
{
    auto EquipmentLogic = UEquipmentLogic::GetEquipmentLogicComponent(Item);
    if (!EquipmentLogic)
        return EEquipmentSlot::None;

    return EquipmentLogic->GetEquipmentSlot();
}
