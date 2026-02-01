// Fill out your copyright notice in the Description page of Project Settings.

#include "UW_MainMenu.h"
#include "Kismet/GameplayStatics.h"
#include "ExfilGameMode.h"

void UUW_MainMenu::StartOpen()
{
    Super::StartOpen();

    auto GameMode = Cast<AExfilGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    if (!GameMode)
        return;

    GameMode->SetPause(true);
}

void UUW_MainMenu::StartClose()
{
    Super::StartClose();

}

void UUW_MainMenu::FinishOpen()
{
    Super::FinishOpen();

}

void UUW_MainMenu::FinishClose()
{
    Super::FinishClose();

    auto GameMode = Cast<AExfilGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    if (!GameMode)
        return;

    GameMode->SetPause(true);
}
