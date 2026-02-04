// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LogicInterface.h"
#include "UW_Base.generated.h"

class ULogicBase;

UCLASS(Abstract, Blueprintable)
class DIPLOMAEXTRACTION_API UUW_Base : public UUserWidget, public ILogicInterface
{
    GENERATED_BODY()

public:
    virtual ULogicBase* GetLogic_Implementation() override;
    virtual void        SetLogic_Implementation(ULogicBase* NewLogic) override;

protected:
    virtual void LogicChanged(ULogicBase* OldLogic, ULogicBase* NewLogic);

private:
    UPROPERTY(Transient)
    ULogicBase* Logic;

    // Initialize child logic
protected:
    virtual void InitializeChildLogic(ULogicBase* NewLogic);

    bool bIsAutoInitializeChildLogic = true;
};
