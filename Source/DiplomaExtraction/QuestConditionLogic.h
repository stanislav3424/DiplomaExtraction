// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LogicBase.h"
#include "QuestConditionLogic.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllQuestsCompleted);

enum class ETypeQuest : uint8;
class UBoxComponent;
class UPresenceDetectorSceneComponent;

UCLASS(NotBlueprintable, Abstract)
class DIPLOMAEXTRACTION_API UQuestConditionLogic : public ULogicBase
{
    GENERATED_BODY()

protected:
    virtual void InitializeRowHandler(FDataTableRowHandle const& InitRowHandle) override;

public:
    TArray<TPair<ETypeQuest, bool>> GetQuestsStatus() { return QuestsStatus.Array(); };
    virtual bool                    ApplyQuestItem(ULogicBase* QuestItem);
    bool                            CheckQuestItem(ULogicBase* QuestItem);
    bool                            IsAreAllQuestsCompleted() const { return AreAllQuestsCompleted; };

    FOnAllQuestsCompleted OnAllQuestsCompleted;

protected:
    void CheckQuestsCompleted();

    TMap<ETypeQuest, bool> QuestsStatus;
    bool                   AreAllQuestsCompleted = false;


};
