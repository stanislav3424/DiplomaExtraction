// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LogicInterface.h"
#include "ActorBase.generated.h"

UCLASS(Abstract, Blueprintable)
class DIPLOMAEXTRACTION_API AActorBase : public AActor, public ILogicInterface
{
	GENERATED_BODY()

public:
    virtual ULogicBase* GetLogic_Implementation() override;
    virtual void        SetLogic_Implementation(ULogicBase* NewLogic) override;

private:
    UPROPERTY(Transient)
    ULogicBase* LogicBase;
};
