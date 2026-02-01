// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ExfilGameMode.generated.h"

class AIconRendering;

UCLASS(Abstract, Blueprintable)
class DIPLOMAEXTRACTION_API AExfilGameMode : public AGameModeBase
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

    UPROPERTY(Transient)
    AIconRendering* IconRenderer;

    UPROPERTY(EditDefaultsOnly, Category = "IconRendererClass")
    TSubclassOf<AIconRendering> IconRendererClass;

public:
    AIconRendering* GetIconRenderer() const { return IconRenderer; }
};
