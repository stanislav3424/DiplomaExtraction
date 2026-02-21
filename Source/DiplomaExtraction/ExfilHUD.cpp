// Fill out your copyright notice in the Description page of Project Settings.

#include "ExfilHUD.h"
#include "UMG.h"
#include "MacroLibrary.h"
#include "LogicLibrary.h"
#include "UW_Dialog.h"
#include "ExfilGameMode.h"

void AExfilHUD::BeginPlay()
{
    Super::BeginPlay();

}

void AExfilHUD::Tick(float Delta)
{
    Super::Tick(Delta);

    if (!PlayerLogic)
        InitHUD();
}

void AExfilHUD::InitHUD()
{
    auto PC = GetOwningPlayerController();
    if (!PC)
        return;
    PlayerLogic = ULogicLibrary::GetLogic(PC->GetPawn());
    if (!PlayerLogic)
        return;

    CHECK_VAR_RETURN(MainMenuWidgetClass)

    MainMenuWidget = CreateWidget<UUW_Dialog>(GetWorld(), MainMenuWidgetClass);
    if (!MainMenuWidget)
        return;
    MainMenuWidget->AddToViewport(5);

    CHECK_VAR_RETURN(PawnInfoWidgetClass)

    PawnInfoWidget = CreateWidget<UUW_Dialog>(GetWorld(), PawnInfoWidgetClass);
    if (!PawnInfoWidget)
        return;
    PawnInfoWidget->AddToViewport(4);

    ULogicLibrary::SetLogic(PawnInfoWidget, PlayerLogic);

    auto GM = AExfilGameMode::Get(GetWorld());
    CHECK_VAR_RETURN(GM)

    GM->OnStatusGameChanged.AddUniqueDynamic(this, &AExfilHUD::OnStatusGameChanged);
    GM->BroadcastStatusGameChanged();
}

void AExfilHUD::OnStatusGameChanged(EStatusGame const& StatusGame)
{
    CHECK_VAR_RETURN(MainMenuWidget)

    if (StatusGame == EStatusGame::NotStarted)
        MainMenuWidget->OpenDialog();
}

void AExfilHUD::ToggleMainMenu()
{
    if (MainMenuWidget)
        MainMenuWidget->ToggleDialog();
}

void AExfilHUD::TogglePawnInfo()
{
    if (PawnInfoWidget)
        PawnInfoWidget->ToggleDialog();
}
