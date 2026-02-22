// Fill out your copyright notice in the Description page of Project Settings.

#include "ExfilGameState.h"
#include "LogicBase.h"

AExfilGameState* AExfilGameState::Get(UObject* WorldContextObject)
{
    if (!GEngine)
        return nullptr;

    auto World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
    if (!World)
        return nullptr;

    return World->GetGameState<AExfilGameState>();
}

void AExfilGameState::QuestCompleted(ULogicBase* LevelQuestLogic)
{
    OnLevelQuestCompleted.Broadcast(LevelQuestLogic);
}
