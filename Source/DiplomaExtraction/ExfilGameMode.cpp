// Fill out your copyright notice in the Description page of Project Settings.

#include "ExfilGameMode.h"
#include "IconRendering.h"
#include "Kismet/GameplayStatics.h"
#include "MacroLibrary.h"

void AExfilGameMode::BeginPlay()
{
    Super::BeginPlay();

    auto World = GetWorld();
    if (!World)
        return;

    CHECK_VAR_RETURN(IconRendererClass)

    IconRenderer = World->SpawnActor<AIconRendering>(IconRendererClass);
    CHECK_VAR_RETURN(IconRenderer)
}

void AExfilGameMode::TogglePause()
{
    SetPauseGame(!bIsPaused);
}

void AExfilGameMode::SetPauseGame(bool bPause)
{
    if (bIsPaused == bPause)
        return;

    bIsPaused = bPause;
    UGameplayStatics::SetGamePaused(GetWorld(), bIsPaused);
    BroadcastGamePausedChanged();
}

void AExfilGameMode::BroadcastGamePausedChanged() const
{
    OnGamePausedChanged.Broadcast(bIsPaused);
}
