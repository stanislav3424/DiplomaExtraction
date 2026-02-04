// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnLibrary.h"
#include "MacroLibrary.h"
#include "LogicBase.h"
#include "Row.h"
#include "CharacterLogic.h"

AActor* USpawnLibrary::SpawnActorByRowHandler(UObject* WorldContextObject, FDataTableRowHandle const& RowHandle,
    FVector const& SpawnLocation, FRotator const& SpawnRotation)
{
    if (!WorldContextObject)
        return nullptr;

    if (!GEngine)
        return nullptr;

    auto World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
    if (!World)
        return nullptr;

    if (RowHandle.IsNull())
        return nullptr;

    auto Logic = SpawnLogicByRowHandler(WorldContextObject, RowHandle);
    if (!Logic)
        return nullptr;

    auto Actor = Logic->SpawnRepresentationActor(SpawnLocation, SpawnRotation);

    return Actor;
}

ULogicBase* USpawnLibrary::SpawnLogicByRowHandler(UObject* WorldContextObject, FDataTableRowHandle const& RowHandle)
{
    if (!WorldContextObject)
        return nullptr;

    if (!GEngine)
        return nullptr;

    auto World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
    if (!World)
        return nullptr;

    if (RowHandle.IsNull())
        return nullptr;

    auto RowStruct = RowHandle.DataTable->GetRowStruct();
    if (RowStruct != FTemplateCharacterRow::StaticStruct())
    {
        auto Row = RowHandle.GetRow<FLogicBaseRow>(FILE_FUNC);
        if (!Row)
            return nullptr;

        auto& Class = Row->LogicClass;
        if (!Class)
            return nullptr;

        auto Logic = NewObject<ULogicBase>(World, Class);
        if (!Logic)
            return nullptr;

        Logic->InitializeRowHandler(RowHandle);

        return Logic;
    }
    else 
    {
        auto Row = RowHandle.GetRow<FTemplateCharacterRow>(FILE_FUNC);
        if (!Row)
            return nullptr;

        if (Row->CharacterRow.IsNull())
            return nullptr;

        if (Row->CharacterRow.DataTable->GetRowStruct() == FCharacterLogicRow::StaticStruct())
        {
            auto CharacterLogic = Cast<UCharacterLogic>(SpawnLogicByRowHandler(World, Row->CharacterRow));

            for (auto& EquipmentSlot : Row->Equipment)
            {
                auto EquipmentLogic = SpawnLogicByRowHandler(World, EquipmentSlot.Value);
                CharacterLogic->EquipItem(EquipmentSlot.Key, EquipmentLogic);
            }

            return CharacterLogic;
        }
    }

    return nullptr;
}
