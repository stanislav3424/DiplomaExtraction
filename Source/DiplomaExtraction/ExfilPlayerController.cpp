// Fill out your copyright notice in the Description page of Project Settings.

#include "ExfilPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MacroLibrary.h"
#include "ExfilHUD.h"

void AExfilPlayerController::BeginPlay()
{
    Super::BeginPlay();

    AddMappingContext();
}

void AExfilPlayerController::AddMappingContext()
{
    CHECK_FIELD_RETURN(UserInterfaceInputMappingContext)

    auto World = GetWorld();
    if (!World)
        return;
    auto LocalPlayer = World->GetFirstLocalPlayerFromController();
    if (!LocalPlayer)
        return;
    auto EnhancedInputLocalPlayerSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
    if (!EnhancedInputLocalPlayerSubsystem)
        return;
    EnhancedInputLocalPlayerSubsystem->AddMappingContext(UserInterfaceInputMappingContext, 0);
}

void AExfilPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
    if (!EnhancedInputComponent)
        return;

    CHECK_FIELD_RETURN(MainMenuInputAction)
    EnhancedInputComponent->BindAction(
        MainMenuInputAction, ETriggerEvent::Started, this, &AExfilPlayerController::OnMainMenu);

    CHECK_FIELD_RETURN(PawnInfoInputAction)
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
