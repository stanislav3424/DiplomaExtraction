// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemLogic.h"
#include "CharacterLogic.h"
#include "SpawnLibrary.h"
#include "MacroLibrary.h"

UItemLogic::UItemLogic()
{
    EquipmentSlot = EEquipmentSlot::None;
}

void UItemLogic::InitializeRowHandler(FDataTableRowHandle const& InitRowHandle)
{
    Super::InitializeRowHandler(InitRowHandle);

    auto Row = InitRowHandle.GetRow<FItemLogicRow>(FILE_FUNC);
    if (!Row)
        return;

    EquipmentSlot = Row->EquipmentSlot;
    if (EquipmentSlot == EEquipmentSlot::None)
        UE_LOG(InitGameLogic, Warning, TEXT("UItemLogic::GetEquipmentSlot: EquipmentSlot is None for ItemLogic %s"),
            *GetName());
}

EEquipmentSlot const& UItemLogic::GetEquipmentSlot() const
{
    if (EquipmentSlot == EEquipmentSlot::None)
        UE_LOG(
            LogTemp, Error, TEXT("UItemLogic::GetEquipmentSlot: EquipmentSlot is None for ItemLogic %s"), *GetName());

    return EquipmentSlot;
}
