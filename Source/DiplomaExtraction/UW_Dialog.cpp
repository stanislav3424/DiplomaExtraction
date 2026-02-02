// Fill out your copyright notice in the Description page of Project Settings.

#include "UW_Dialog.h" 
#include "Animation/WidgetAnimation.h"

void UUW_Dialog::NativeConstruct()
{
    Super::NativeConstruct();
    SetVisibility(ESlateVisibility::Hidden);
    CloseDialog();
}

void UUW_Dialog::ToggleDialog()
{
    if (bIsOpen)
        CloseDialog();
    else
        OpenDialog();
}

void UUW_Dialog::OpenDialog()
{
    if (bIsOpen)
        return;

    auto World = GetWorld();
    if (!World)
        return;

    StartOpen();

    World->GetTimerManager().ClearTimer(FinishTimerHandle);
    SetVisibility(ESlateVisibility::Visible);
    bIsOpen = true;
    if (DialogAnimation)
    {
        PlayAnimation(DialogAnimation, 0.f, 1, EUMGSequencePlayMode::Forward);
        const float Duration = DialogAnimation->GetEndTime();

        World->GetTimerManager().SetTimer(FinishTimerHandle, this, &UUW_Dialog::FinishOpen, Duration, false);
    }
    else
        FinishOpen();
}

void UUW_Dialog::CloseDialog()
{
    if (!bIsOpen)
        return;

    auto World = GetWorld();
    if (!World)
        return;

    StartClose();

    World->GetTimerManager().ClearTimer(FinishTimerHandle);
    if (DialogAnimation)
    {
        PlayAnimation(DialogAnimation, 0.f, 1, EUMGSequencePlayMode::Reverse);
        const float Duration = DialogAnimation->GetEndTime();
        World->GetTimerManager().SetTimer(FinishTimerHandle, this, &UUW_Dialog::FinishClose, Duration, false);
    }
    else
        FinishClose();
}

void UUW_Dialog::FinishOpen()
{
}

void UUW_Dialog::FinishClose()
{
    SetVisibility(ESlateVisibility::Hidden);
    bIsOpen = false;
}
