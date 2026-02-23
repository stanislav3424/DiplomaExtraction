// Fill out your copyright notice in the Description page of Project Settings.

#include "InitRowHandle.h"
#include "MacroLibrary.h"
#include "SpawnLibrary.h"
#include "LogicLibrary.h"
#include "LogicBase.h"

void UInitRowHandle::BeginPlay()
{
    Super::BeginPlay();

    auto World = GetWorld();
    CHECK_VAR_RETURN(World);

    FTimerHandle TimerHandle;
    World->GetTimerManager().SetTimer(TimerHandle, this, &UInitRowHandle::Init, 0.1f, false);
}

void UInitRowHandle::Init()
{
    auto Actor = GetOwner();
    CHECK_VAR_RETURN(Actor);

    if (InitRowHandle.IsNull())
    {
        UE_LOG(InitGameLogic, Error, TEXT("InitRowHandle is null for owner %s"), *Actor->GetName());
        return;
    }

    auto CurrentLogic = ULogicLibrary::GetLogic(Actor);
    if (CurrentLogic)
        return;

    auto Logic = USpawnLibrary::SpawnLogicByRowHandler(GetWorld(), InitRowHandle, Actor);
    CHECK_VAR_RETURN(Logic);

    Logic->OnGround();
}
