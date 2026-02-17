// Fill out your copyright notice in the Description page of Project Settings.

#include "AutoAddLogicActorComponent.h"
#include "MacroLibrary.h"
#include "SpawnLibrary.h"
#include "LogicLibrary.h"
#include "LogicBase.h"

ULogicBase* UAutoAddLogicActorComponent::GetLogic_Implementation()
{
    return LogicBase;
}

void UAutoAddLogicActorComponent::SetLogic_Implementation(ULogicBase* NewLogic)
{
    LogicBase = NewLogic;

    if (!NewLogic)
        return;

    CHECK_VAR_RETURN(!DataTableRowHandle.IsNull());

    auto Logic = USpawnLibrary::SpawnLogicByRowHandler(GetWorld(), DataTableRowHandle);
    CHECK_VAR_RETURN(Logic);

    NewLogic->AddLogicComponent(Logic);

    if (auto World = GetWorld())
        World->GetTimerManager().SetTimerForNextTick([this]() { DestroyComponent(); });
}
