// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DetourCrowdAIController.h"
#include "DetourCrowdAIC_Base.generated.h"

UCLASS(Abstract, Blueprintable)
class DIPLOMAEXTRACTION_API ADetourCrowdAIC_Base : public ADetourCrowdAIController
{
    GENERATED_BODY()

public:
    virtual void OnPossess(APawn* InPawn) override;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "AI")
    UBehaviorTree* BehaviorTreeAsset;
};
