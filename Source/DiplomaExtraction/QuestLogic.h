// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LogicBase.h"
#include "QuestLogic.generated.h"

enum class ETypeQuest : uint8;

UCLASS(NotBlueprintable)
class DIPLOMAEXTRACTION_API UQuestLogic : public ULogicBase
{
    GENERATED_BODY()

    UQuestLogic();

protected:
    virtual void InitializeRowHandler(FDataTableRowHandle const& InitRowHandle) override;

public:
    ETypeQuest GetTypeQuest() const { return TypeQuest; };

private:
    ETypeQuest TypeQuest;
};
