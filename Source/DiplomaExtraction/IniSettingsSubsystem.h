// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "IniSettingsSubsystem.generated.h"

UCLASS(config = Game, defaultconfig)
class DIPLOMAEXTRACTION_API UIniSettingsSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    static UIniSettingsSubsystem* Get(UObject* WorldContextObject);

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    UFUNCTION(BlueprintCallable)
    float GetEnemySpawnInterval() const { return EnemySpawnInterval; };

private:
    UPROPERTY(Config)
    float EnemySpawnInterval = 5.f;
};
