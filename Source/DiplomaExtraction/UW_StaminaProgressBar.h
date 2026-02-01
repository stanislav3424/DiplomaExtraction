// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UW_ProgressBarBase.h"
#include "UW_StaminaProgressBar.generated.h"

UCLASS(Abstract, Blueprintable)
class DIPLOMAEXTRACTION_API UUW_StaminaProgressBar : public UUW_ProgressBarBase
{
    GENERATED_BODY()

protected:
    virtual void LogicChanged(ULogicBase* OldLogic, ULogicBase* NewLogic) override;
};
