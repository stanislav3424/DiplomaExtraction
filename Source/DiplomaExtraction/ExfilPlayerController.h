// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ExfilPlayerController.generated.h"

UCLASS(Abstract, Blueprintable)
class DIPLOMAEXTRACTION_API AExfilPlayerController : public APlayerController
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
};
