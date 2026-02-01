// Fill out your copyright notice in the Description page of Project Settings.

#include "ExfilGameMode.h"
#include "IconRendering.h"
#include "Kismet/GameplayStatics.h"

void AExfilGameMode::BeginPlay()
{
    Super::BeginPlay();

    auto World = GetWorld();
    if (!World)
        return;

    IconRenderer = World->SpawnActor<AIconRendering>(IconRendererClass);
}

void AExfilGameMode::TogglePause()
{
    SetPause(!bIsPaused);
}

void AExfilGameMode::SetPause(bool bPause)
{
    bIsPaused = bPause;
    UGameplayStatics::SetGamePaused(GetWorld(), bIsPaused);
    BroadcastGamePausedChanged();
}

void AExfilGameMode::BroadcastGamePausedChanged() const
{
    OnGamePausedChanged.Broadcast(bIsPaused);
}
