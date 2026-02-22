// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestConditionLogic.h"
#include "ListenQuestConditionLogic.generated.h"

UCLASS(NotBlueprintable)
class DIPLOMAEXTRACTION_API UListenQuestConditionLogic : public UQuestConditionLogic
{
    GENERATED_BODY()

protected:
    virtual void InitializeRowHandler(FDataTableRowHandle const& InitRowHandle);

    UFUNCTION()
    void OnLevelQuestCompleted(ULogicBase* LevelQuestLogic);

    bool bIsListenLevelQuest = true;
};
