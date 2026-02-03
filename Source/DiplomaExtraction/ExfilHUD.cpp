// Fill out your copyright notice in the Description page of Project Settings.

#include "ExfilHUD.h"
#include "UMG.h"
#include "MacroLibrary.h"
#include "LogicLibrary.h"
#include "UW_Dialog.h" 

void AExfilHUD::BeginPlay()
{
    Super::BeginPlay();


}

void AExfilHUD::InitHUD()
{
    CHECK_FIELD_RETURN(MainMenuWidgetClass)

    MainMenuWidget = CreateWidget<UUW_Dialog>(GetWorld(), MainMenuWidgetClass);
    if (!MainMenuWidget)
        return;
    MainMenuWidget->AddToViewport(5);

    CHECK_FIELD_RETURN(PawnInfoWidgetClass)

    PawnInfoWidget = CreateWidget<UUW_Dialog>(GetWorld(), PawnInfoWidgetClass);
    if (!PawnInfoWidget)
        return;
    PawnInfoWidget->AddToViewport(4);

    auto PC = GetOwningPlayerController();
    if (!PC)
        return;
    auto PlayerLogic = ULogicLibrary::GetLogic(PC->GetPawn());
    CHECK_FIELD_RETURN(PlayerLogic)
    ULogicLibrary::SetLogic(PawnInfoWidget, PlayerLogic);
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
