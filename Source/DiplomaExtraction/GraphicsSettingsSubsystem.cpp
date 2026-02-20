// Fill out your copyright notice in the Description page of Project Settings.

#include "GraphicsSettingsSubsystem.h"
#include "GameFramework/GameUserSettings.h"

UGraphicsSettingsSubsystem* UGraphicsSettingsSubsystem::Get(UObject* WorldContextObject)
{
    if (!GEngine)
        return nullptr;

    auto World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
    if (!World)
        return nullptr;

    auto GameInstance = World->GetGameInstance();
    if (!GameInstance)
        return nullptr;

    return GameInstance->GetSubsystem<UGraphicsSettingsSubsystem>();
}

    //auto* Settings = GEngine->GetGameUserSettings();
    //Settings->SetViewDistanceQuality(3);
    //Settings->SetAntiAliasingQuality(2);
    //Settings->SetPostProcessingQuality(3);
    //Settings->SetShadowQuality(4);
    //Settings->SetGlobalIlluminationQuality(3);
    //Settings->SetReflectionQuality(3);
    //Settings->SetTextureQuality(2);
    //Settings->SetVisualEffectQuality(3);
    //Settings->SetFoliageQuality(3);
    //Settings->SetShadingQuality(3);
    //Settings->ApplySettings(false);

