// Fill out your copyright notice in the Description page of Project Settings.

#include "ExfilPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MacroLibrary.h"
#include "ExfilHUD.h"
#include "ExfilGameMode.h"
#include "LevelSequence.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"

void AExfilPlayerController::BeginPlay()
{
    Super::BeginPlay();

    auto GameMode = AExfilGameMode::Get(GetWorld());
    CHECK_VAR_RETURN(GameMode);

    GameMode->OnStatusGameChanged.AddUniqueDynamic(this, &AExfilPlayerController::OnStatusGameChanged);
    OnStatusGameChanged(GameMode->GetStatusGame());

    CHECK_VAR(!ArrLevelSequence.IsEmpty());
    for (auto LevelSequence : ArrLevelSequence)
        CHECK_VAR(LevelSequence);

    CHECK_VAR(GameEndLevelSequence);
}

void AExfilPlayerController::OnStatusGameChanged(EStatusGame const& NewStatusGame)
{
    RemoveMappingContext();
    StopLevelSequence();

    switch (NewStatusGame)
    {
        case EStatusGame::NotStarted:
            EnterCinematicMode();
            break;
        case EStatusGame::Started:
            EnterDefaultMode();
            break;
        case EStatusGame::Over:
            PlayGameEndLevelSequence();
            break;
        default:
            break;
    }
}

void AExfilPlayerController::AddMappingContext()
{
    CHECK_VAR_RETURN(UserInterfaceInputMappingContext)

    auto LocalPlayer = GetLocalPlayer();
    if (!LocalPlayer)
        return;

    auto EnhancedInputLocalPlayerSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
    if (!EnhancedInputLocalPlayerSubsystem)
        return;

    EnhancedInputLocalPlayerSubsystem->AddMappingContext(UserInterfaceInputMappingContext, 0);
}

void AExfilPlayerController::RemoveMappingContext()
{
    CHECK_VAR_RETURN(UserInterfaceInputMappingContext)

    auto LocalPlayer = GetLocalPlayer();
    if (!LocalPlayer)
        return;

    auto EnhancedInputLocalPlayerSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
    if (!EnhancedInputLocalPlayerSubsystem)
        return;

    EnhancedInputLocalPlayerSubsystem->RemoveMappingContext(UserInterfaceInputMappingContext);
}

void AExfilPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
    if (!EnhancedInputComponent)
        return;

    CHECK_VAR_RETURN(MainMenuInputAction)
    EnhancedInputComponent->BindAction(
        MainMenuInputAction, ETriggerEvent::Started, this, &AExfilPlayerController::OnMainMenu);

    CHECK_VAR_RETURN(PawnInfoInputAction)
    EnhancedInputComponent->BindAction(
        PawnInfoInputAction, ETriggerEvent::Started, this, &AExfilPlayerController::OnPawnInfo);
}

void AExfilPlayerController::OnMainMenu(FInputActionValue const& Value)
{
    auto HUD = GetHUD<AExfilHUD>();
    if (!HUD)
        return;

    HUD->ToggleMainMenu();
}

void AExfilPlayerController::OnPawnInfo(FInputActionValue const& Value)
{
    auto HUD = GetHUD<AExfilHUD>();
    if (!HUD)
        return;

    HUD->TogglePawnInfo();
}

void AExfilPlayerController::EnterCinematicMode()
{
    PlayLevelSequence();
}

void AExfilPlayerController::EnterDefaultMode()
{
    AddMappingContext();
}

void AExfilPlayerController::EnterSpectatorMode()
{
}

void AExfilPlayerController::PlayLevelSequence()
{
    StopLevelSequence();

    CHECK_VAR_RETURN(!ArrLevelSequence.IsEmpty())
    int32 Index = FMath::RandHelper(ArrLevelSequence.Num());

    auto LevelSequence = ArrLevelSequence[Index];
    CHECK_VAR_RETURN(LevelSequence)

    FMovieSceneSequencePlaybackSettings Settings;
    Settings.bHidePlayer                    = true;
    Settings.bDisableMovementInput          = true;
    ALevelSequenceActor* LevelSequenceActor = nullptr;
    LevelSequencePlayer =
        ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LevelSequence, Settings, LevelSequenceActor);
    if (!LevelSequencePlayer)
        return;

    LevelSequencePlayer->Play();
    LevelSequencePlayer->OnFinished.AddUniqueDynamic(this, &AExfilPlayerController::PlayLevelSequence);
}

void AExfilPlayerController::StopLevelSequence()
{
    if (!LevelSequencePlayer)
        return;

    LevelSequencePlayer->OnFinished.RemoveAll(this);
    LevelSequencePlayer->Stop();

    LevelSequencePlayer = nullptr;
}

void AExfilPlayerController::PlayGameEndLevelSequence()
{
    CHECK_VAR_RETURN(GameEndLevelSequence)

    FMovieSceneSequencePlaybackSettings Settings;
    Settings.bHidePlayer                    = true;
    Settings.bDisableMovementInput          = true;
    ALevelSequenceActor* LevelSequenceActor = nullptr;
    LevelSequencePlayer =
        ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), GameEndLevelSequence, Settings, LevelSequenceActor);
    if (!LevelSequencePlayer)
        return;

    LevelSequencePlayer->Play();

    LevelSequencePlayer->OnFinished.AddUniqueDynamic(this, &AExfilPlayerController::GameEnd);
}

void AExfilPlayerController::GameEnd()
{
    auto GameMode = AExfilGameMode::Get(GetWorld());
    CHECK_VAR_RETURN(GameMode);

    GameMode->ReloadGame();
}
