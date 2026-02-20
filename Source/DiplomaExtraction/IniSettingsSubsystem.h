// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "IniSettingsSubsystem.generated.h"

UCLASS()
class DIPLOMAEXTRACTION_API UIniSettingsSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    static UIniSettingsSubsystem* Get(UObject* WorldContextObject);
};
