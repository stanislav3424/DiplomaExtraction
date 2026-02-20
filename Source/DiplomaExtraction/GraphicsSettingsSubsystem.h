// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GraphicsSettingsSubsystem.generated.h"

UCLASS()
class DIPLOMAEXTRACTION_API UGraphicsSettingsSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    static UGraphicsSettingsSubsystem* Get(UObject* WorldContextObject);

};
