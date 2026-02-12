// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnerActor.h"
#include "PresenceDetectorSceneComponent.h"
#include "LogicBase.h"
#include "HealthLogic.h"
#include "SpawnLibrary.h"
#include "MacroLibrary.h"
#include "LogicLibrary.h"

void ASpawnerActor::BeginPlay()
{
    Super::BeginPlay();

    PrimaryActorTick.TickInterval = TickInterval;
    PrimaryActorTick.bCanEverTick = true;

    FillQueue();
}

void ASpawnerActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    SpawnUnit();
}

void ASpawnerActor::FillQueue()
{
    for (auto const& TypeUnits : Units)
        for (int32 Index = 0; Index < TypeUnits.Count; ++Index)
            Queue.Enqueue(TypeUnits.UnataTableRowHandleit);
}

void ASpawnerActor::SpawnUnit()
{
    FDataTableRowHandle DataTableRowHandle;

    if (!Queue.Dequeue(DataTableRowHandle))
        return;

    FVector SpawnLocation = GetActorLocation();
    FRotator SpawnRotation = GetActorRotation();

    auto Actor = USpawnLibrary::SpawnActorByRowHandler(GetWorld(), DataTableRowHandle, SpawnLocation, SpawnRotation);
    CHECK_FIELD_RETURN(Actor);

    auto Logic = ULogicLibrary::GetLogic(Actor);
    CHECK_FIELD_RETURN(Logic);

    auto HealthLogic = Logic->GetLogicComponent<UHealthLogic>();
    CHECK_FIELD_RETURN(HealthLogic);

    HealthLogic->OnDeathInfo.AddUniqueDynamic(this, &ASpawnerActor::OnDeathUnit);
}

void ASpawnerActor::OnDeathUnit(ULogicBase* LogicBase, AActor* Actor)
{
    auto const& RowHandle = LogicBase->GetRowHandle();

    Queue.Enqueue(RowHandle);
}
