// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LogicInterface.h"
#include "CharacterBase.generated.h"

class ULogicBase;

/**
 *
 */
UCLASS(Abstract, NotBlueprintable)
class DIPLOMAEXTRACTION_API ACharacterBase : public ACharacter, public ILogicInterface
{
    GENERATED_BODY()

public:
    virtual ULogicBase* GetLogic_Implementation() override;
    virtual void        SetLogic_Implementation(ULogicBase* NewLogic) override;

private:
    UPROPERTY(Transient)
    ULogicBase* Logic;
};
