// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterLogic.h"
#include "SpawnLibrary.h"
#include "ItemLogic.h"

void UCharacterLogic::InitializeRowHandler(FDataTableRowHandle const& InitRowHandle)
{
    Super::InitializeRowHandler(InitRowHandle);
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
    Item->SetOwnerLogic(this);

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
    Item->SetOwnerLogic(nullptr);

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

UItemLogic* UCharacterLogic::GetItemLogicComponent(ULogicBase* Item)
{
    auto ItemLogic = Cast<UItemLogic>(Item->GetLogicComponent<UItemLogic>(UItemLogic::StaticClass()));
    if (!ItemLogic)
        return nullptr;
    return ItemLogic;
}

EEquipmentSlot UCharacterLogic::GetEquipmentSlot(ULogicBase* Item)
{
    auto ItemLogic = GetItemLogicComponent(Item);
    if (!ItemLogic)
        return EEquipmentSlot::None;

    return ItemLogic->GetEquipmentSlot();
}
