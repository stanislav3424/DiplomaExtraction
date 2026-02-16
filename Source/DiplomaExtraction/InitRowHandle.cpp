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
    CHECK_FIELD_RETURN(World);

    FTimerHandle TimerHandle;
    World->GetTimerManager().SetTimer(TimerHandle, this, &UInitRowHandle::Init, 0.1f, false);
}

void UInitRowHandle::Init()
{
    CHECK_FIELD_RETURN(!InitRowHandle.IsNull());

    auto Actor = GetOwner();
    CHECK_FIELD_RETURN(Actor);

    auto CurrentLogic = ULogicLibrary::GetLogic(Actor);
    if (CurrentLogic)
        return;

    auto Logic = USpawnLibrary::SpawnLogicByRowHandler(GetWorld(), InitRowHandle, Actor);
    CHECK_FIELD_RETURN(Logic);

    Logic->OnGround();
}
