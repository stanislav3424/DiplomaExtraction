// Fill out your copyright notice in the Description page of Project Settings.

#include "ExfilGameMode.h"
#include "IconRendering.h"
#include "Kismet/GameplayStatics.h"
#include "MacroLibrary.h"
#include "LevelStartSubsystem.h"

AExfilGameMode* AExfilGameMode::Get(UObject* WorldContextObject)
{
    if (!GEngine)
        return nullptr;

    auto World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
    if (!World)
        return nullptr;

    return World->GetAuthGameMode<AExfilGameMode>();
}

void AExfilGameMode::BeginPlay()
{
    Super::BeginPlay();

    SpawnIconRendering();
    LevelStartSetting();
}

void AExfilGameMode::SpawnIconRendering()
{
    auto World = GetWorld();
    if (!World)
        return;

    CHECK_VAR_RETURN(IconRendererClass)

    IconRenderer = World->SpawnActor<AIconRendering>(IconRendererClass);
    CHECK_VAR_RETURN(IconRenderer)
}

void AExfilGameMode::LevelStartSetting()
{
    auto LevelStartSubsystem = ULevelStartSubsystem::Get(GetWorld());
    if (!LevelStartSubsystem)
        return;

    if (LevelStartSubsystem->GetAutoStartGame())
        StartGame();
}

AIconRendering* AExfilGameMode::GetIconRenderer(UObject* WorldContextObject)
{
    auto GameMode = AExfilGameMode::Get(WorldContextObject);
    if (!GameMode)
        return nullptr;
   
    return GameMode->GetIconRenderer();
}

void AExfilGameMode::TogglePause()
{
    SetPauseGame(!bIsPaused);
}

void AExfilGameMode::SetPauseGame(bool bPause)
{
    if (StatusGame != EStatusGame::Started)
        return;

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

void AExfilGameMode::BroadcastStatusGameChanged() const
{
    OnStatusGameChanged.Broadcast(StatusGame);
}

void AExfilGameMode::SetStatusGame(EStatusGame const& NewStatusGame)
{
    if (StatusGame == NewStatusGame)
        return;

    StatusGame = NewStatusGame;
    BroadcastStatusGameChanged();
}

void AExfilGameMode::StartGame()
{
    if (StatusGame != EStatusGame::NotStarted)
        return;

    SetStatusGame(EStatusGame::Started);
}

void AExfilGameMode::EndGame()
{
    if (StatusGame != EStatusGame::Started)
        return;

    SetStatusGame(EStatusGame::Over);

}

void AExfilGameMode::ReloadGame()
{
    auto LevelStartSubsystem = ULevelStartSubsystem::Get(GetWorld());
    if (!LevelStartSubsystem)
        return;

    LevelStartSubsystem->SetAutoStartGame(false);

    auto World = GetWorld();
    if (!World)
        return;
    FName CurrentLevel = *World->GetMapName();
    UGameplayStatics::OpenLevel(World, CurrentLevel);
}

void AExfilGameMode::ReloadGameAndStartGame()
{
    auto LevelStartSubsystem = ULevelStartSubsystem::Get(GetWorld());
    if (!LevelStartSubsystem)
        return;

    LevelStartSubsystem->SetAutoStartGame(true);

     auto World = GetWorld();
    if (!World)
        return;
    FName CurrentLevel = *World->GetMapName();
    UGameplayStatics::OpenLevel(World, CurrentLevel);
}
