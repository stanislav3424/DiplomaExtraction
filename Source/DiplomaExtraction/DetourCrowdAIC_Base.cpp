// Fill out your copyright notice in the Description page of Project Settings.

#include "DetourCrowdAIC_Base.h"
#include "MacroLibrary.h"

void ADetourCrowdAIC_Base::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    CHECK_FIELD_RETURN(BehaviorTreeAsset)
    RunBehaviorTree(BehaviorTreeAsset);
}