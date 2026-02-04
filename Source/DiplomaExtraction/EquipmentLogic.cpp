// Fill out your copyright notice in the Description page of Project Settings.

#include "EquipmentLogic.h"
#include "CharacterLogic.h"
#include "SpawnLibrary.h"
#include "MacroLibrary.h"
#include "Row.h"
#include "EnumLibrary.h"

UEquipmentLogic::UEquipmentLogic()
{
    EquipmentSlot = EEquipmentSlot::None;
}

void UEquipmentLogic::InitializeRowHandler(FDataTableRowHandle const& InitRowHandle)
{
    Super::InitializeRowHandler(InitRowHandle);

    auto Row = InitRowHandle.GetRow<FEquipmentLogicRow>(FILE_FUNC);
    if (!Row)
        return;

    EquipmentSlot = Row->EquipmentSlot;
    if (EquipmentSlot == EEquipmentSlot::None)
        UE_LOG(InitGameLogic, Warning, TEXT("UItemLogic::GetEquipmentSlot: EquipmentSlot is None for ItemLogic %s"),
            *GetName());
}

EEquipmentSlot const& UEquipmentLogic::GetEquipmentSlot() const
{
    if (EquipmentSlot == EEquipmentSlot::None)
        UE_LOG(
            LogTemp, Error, TEXT("UItemLogic::GetEquipmentSlot: EquipmentSlot is None for ItemLogic %s"), *GetName());

    return EquipmentSlot;
}


UEquipmentLogic* UEquipmentLogic::GetEquipmentLogicComponent(ULogicBase* Item)
{
    auto EquipmentLogic = Cast<UEquipmentLogic>(Item->GetLogicComponent<UEquipmentLogic>());
    if (!EquipmentLogic)
        return nullptr;
    return EquipmentLogic;
}
