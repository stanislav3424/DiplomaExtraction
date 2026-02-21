// Fill out your copyright notice in the Description page of Project Settings.

#include "IniSettingsSubsystem.h"
#include "MacroLibrary.h"

UIniSettingsSubsystem* UIniSettingsSubsystem::Get(UObject* WorldContextObject)
{
    if (!GEngine)
        return nullptr;

    auto World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
    if (!World)
        return nullptr;

    auto GameInstance = World->GetGameInstance();
    if (!GameInstance)
        return nullptr;

    return GameInstance->GetSubsystem<UIniSettingsSubsystem>();
}

void UIniSettingsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    auto Class = GetClass();
    if (!Class)
        return;

    FString DefaultConfig = Class->GetDefaultConfigFilename();
    LoadConfig(Class, *DefaultConfig);

    UE_LOG(InitGameLogic, Log, TEXT("Loaded config file: %s"), *DefaultConfig);
    UE_LOG(InitGameLogic, Log, TEXT("EnemySpawnInterval: %f"), EnemySpawnInterval);
}
