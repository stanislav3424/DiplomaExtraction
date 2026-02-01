// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnLibrary.h"
#include "MacroLibrary.h"
#include "LogicBase.h"

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

    auto LogicRow = RowHandle.GetRow<FLogicBaseRow>(FILE_FUNC);
    if (!LogicRow)
        return nullptr;

    auto& Class = LogicRow->LogicClass;
    if (!Class)
        return nullptr;

    auto Logic = NewObject<ULogicBase>(World, Class);
    if (!Logic)
        return nullptr;

    Logic->InitializeRowHandler(RowHandle);

    return Logic;
}
