// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnerActor.h"
#include "PresenceDetectorSceneComponent.h"
#include "LogicBase.h"
#include "HealthLogic.h"
#include "SpawnLibrary.h"
#include "MacroLibrary.h"
#include "LogicLibrary.h"

ASpawnerActor::ASpawnerActor()
{
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

    PresenceDetector = CreateDefaultSubobject<UPresenceDetectorSceneComponent>(TEXT("PresenceDetector"));
    PresenceDetector->SetupAttachment(RootComponent);

    PrimaryActorTick.bCanEverTick = true;
}

void ASpawnerActor::BeginPlay()
{
    Super::BeginPlay();

    FillQueue();
}

void ASpawnerActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    CHECK_VAR_RETURN(PresenceDetector)
    if (PresenceDetector->IsInside())
        return;

    SpawnUnit();
}

void ASpawnerActor::FillQueue()
{
    if (Units.IsEmpty())
    {
        UE_LOG(InitGameLogic, Error, FILE_FUNC TEXT("Units array is empty — nothing to enqueue"));
    }

    for (auto const& TypeUnits : Units)
        for (int32 Index = 0; Index < TypeUnits.Count; ++Index)
        {
            if (TypeUnits.DataTableRowHandle.IsNull())
            {
                UE_LOG(InitGameLogic, Error, FILE_FUNC TEXT("DataTableRowHandle is NULL at Index=%d (Count=%d)"), Index,
                    TypeUnits.Count);
                break;
            }

            Queue.Enqueue(TypeUnits.DataTableRowHandle);
        }
}

void ASpawnerActor::SpawnUnit()
{
    FDataTableRowHandle DataTableRowHandle;

    if (!Queue.Dequeue(DataTableRowHandle))
        return;

    if (DataTableRowHandle.IsNull())
        return;

    FVector  SpawnLocation = GetActorLocation();
    FRotator SpawnRotation = GetActorRotation();

    auto Actor = USpawnLibrary::SpawnActorByRowHandler(GetWorld(), DataTableRowHandle, SpawnLocation, SpawnRotation);
    CHECK_VAR_RETURN(Actor);

    auto Logic = ULogicLibrary::GetLogic(Actor);
    CHECK_VAR_RETURN(Logic);

    auto HealthLogic = Logic->GetLogicComponent<UHealthLogic>();
    CHECK_VAR_RETURN(HealthLogic);

    HealthLogic->OnDeathInfo.AddUniqueDynamic(this, &ASpawnerActor::OnDeathUnit);

    SpawnedUnits.Add(Actor, DataTableRowHandle);
}

void ASpawnerActor::OnDeathUnit(ULogicBase* LogicBase, AActor* Actor)
{
    FDataTableRowHandle RowHandle;
    if (SpawnedUnits.RemoveAndCopyValue(Actor, RowHandle))
        Queue.Enqueue(RowHandle);
}
