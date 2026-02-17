// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LogicBase.h"
#include "FirstAidKitLogic.generated.h"

UCLASS(Blueprintable)
class DIPLOMAEXTRACTION_API UFirstAidKitLogic : public ULogicBase
{
    GENERATED_BODY()

    // Initialize
public:
    virtual void InitializeRowHandler(FDataTableRowHandle const& InitRowHandle) override;

private:
    void InitializeFirstAidKit();

    // FirstAidKit Functionality
public:
    void Apply();

private:
    float Heal = 100.f;
};
