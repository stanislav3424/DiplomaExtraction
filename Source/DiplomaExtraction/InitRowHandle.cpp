// Fill out your copyright notice in the Description page of Project Settings.

#include "InitRowHandle.h"
#include "MacroLibrary.h"
#include "SpawnLibrary.h"
#include "LogicBase.h"

void UInitRowHandle::BeginPlay()
{
    Super::BeginPlay();

    auto Actor = GetOwner();
    CHECK_FIELD_RETURN(Actor);
    CHECK_FIELD_RETURN(!InitRowHandle.IsNull());
    auto Logic = USpawnLibrary::SpawnLogicByRowHandler(GetWorld(), InitRowHandle, Actor);
    CHECK_FIELD_RETURN(Logic);
}


