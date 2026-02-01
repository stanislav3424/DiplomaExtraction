// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstanceBase.generated.h"

class UCharacterLogic;

UCLASS(Abstract, Blueprintable)
class DIPLOMAEXTRACTION_API UAnimInstanceBase : public UAnimInstance
{
    GENERATED_BODY()

protected:
    virtual void NativeBeginPlay() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "AnimInstance")
    float Rotate = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "AnimInstance")
    float Speed = 0.0f;

    UPROPERTY(BlueprintReadOnly, Category = "AnimInstance")
    bool bIsWeaponEquipped = false;

    UPROPERTY(Transient)
    UCharacterLogic* CharacterLogic;

    UPROPERTY(Transient)
    APawn* Pawn;
};
