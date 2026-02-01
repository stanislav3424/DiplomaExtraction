// Fill out your copyright notice in the Description page of Project Settings.

#include "UW_ProgressBarBase.h"
#include "Components/ProgressBar.h"

void UUW_ProgressBarBase::SetPercent(float Current, float Max)
{
    if (ProgressBar)
        ProgressBar->SetPercent(FMath::Clamp(Current / Max, 0.0f, 1.0f));
}
