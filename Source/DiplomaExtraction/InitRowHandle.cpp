// Fill out your copyright notice in the Description page of Project Settings.

#include "InitRowHandle.h"
#include "MacroLibrary.h"
#include "SpawnLibrary.h"
#include "LogicBase.h"

void UInitRowHandle::BeginPlay()
{
    Super::BeginPlay();

    CHECK_FIELD_RETURN(!InitRowHandle.IsNull());

    auto Owner = GetOwner();
    if (!Owner)
        return;

    const bool bLoaded = Owner->HasAnyFlags(RF_WasLoaded);
    switch (TypeInit)
    {
        case ETypeInit::PlacedInWorld:
            if (bLoaded)
                Init();
            break;
        case ETypeInit::Spawned:
            if (!bLoaded)
                Init();
            break;
        case ETypeInit::PlacedInWorldOrSpawned:
            Init();
            break;
        default:
            break;
    }
}

void UInitRowHandle::Init()
{
    auto Actor = GetOwner();
    CHECK_FIELD_RETURN(Actor);
    CHECK_FIELD_RETURN(!InitRowHandle.IsNull());
    auto Logic = USpawnLibrary::SpawnLogicByRowHandler(GetWorld(), InitRowHandle, Actor);
    CHECK_FIELD_RETURN(Logic);
    Logic->SetSimulatePhysics();
}
