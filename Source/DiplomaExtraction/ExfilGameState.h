// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ExfilGameState.generated.h"

class ULogicBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelQuestCompleted, ULogicBase*, LevelQuestLogic);

UCLASS(NotBlueprintable)
class DIPLOMAEXTRACTION_API AExfilGameState : public AGameStateBase
{
    GENERATED_BODY()

public:
    static AExfilGameState* Get(UObject* WorldContextObject);

    FOnLevelQuestCompleted OnLevelQuestCompleted;

    void QuestCompleted(ULogicBase* LevelQuestLogic);
};
