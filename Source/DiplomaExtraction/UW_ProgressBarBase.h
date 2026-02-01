// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UW_Base.h"
#include "UW_ProgressBarBase.generated.h"

class UProgressBar;

UCLASS(Abstract, NotBlueprintable)
class DIPLOMAEXTRACTION_API UUW_ProgressBarBase : public UUW_Base
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UProgressBar* ProgressBar;

    UFUNCTION()
    void SetPercent(float Current, float Max);
};
