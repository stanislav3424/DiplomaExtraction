// Fill out your copyright notice in the Description page of Project Settings.

#include "ListenQuestConditionLogic.h"
#include "ExfilGameState.h"
#include "MacroLibrary.h"

void UListenQuestConditionLogic::InitializeRowHandler(FDataTableRowHandle const& InitRowHandle)
{
    Super::InitializeRowHandler(InitRowHandle);

    auto GameState = AExfilGameState::Get(GetWorld());
    CHECK_VAR_RETURN(GameState);

    GameState->OnLevelQuestCompleted.AddUniqueDynamic(this, &UListenQuestConditionLogic::OnLevelQuestCompleted);
}

void UListenQuestConditionLogic::OnLevelQuestCompleted(ULogicBase* LevelQuestLogic)
{
    if (bIsListenLevelQuest)
        ApplyQuestItem(LevelQuestLogic);
}
