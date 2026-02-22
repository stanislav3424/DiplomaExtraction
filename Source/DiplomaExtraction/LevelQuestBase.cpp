// Fill out your copyright notice in the Description page of Project Settings.

#include "LevelQuestBase.h"
#include "MacroLibrary.h"
#include "EngineUtils.h"

ALevelQuestBase* ALevelQuestBase::Instance = nullptr;

ALevelQuestBase* ALevelQuestBase::Get(UObject* WorldContextObject)
{
    if (!GEngine)
        return nullptr;

    auto World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
    if (!World)
        return nullptr;

    if (Instance && Instance->GetWorld() == World)
        return Instance;

    for (TActorIterator<ALevelQuestBase> It(World); It; ++It)
    {
        Instance = *It;
        return Instance;
    }

    return nullptr;
}

void ALevelQuestBase::BeginPlay()
{
    Super::BeginPlay();

    if (Instance != this)
    {
        CHECK_VAR(!Instance);

        Destroy();
        return;
    }
}
