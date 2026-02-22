// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelQuestBase.generated.h"

UCLASS(Blueprintable)
class DIPLOMAEXTRACTION_API ALevelQuestBase : public AActor
{
    GENERATED_BODY()

public:
    static ALevelQuestBase* Get(UObject* WorldContextObject);

private:
    static ALevelQuestBase* Instance;

protected:
    virtual void BeginPlay() override;
};
