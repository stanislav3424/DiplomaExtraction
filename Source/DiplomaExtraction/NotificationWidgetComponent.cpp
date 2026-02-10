// Fill out your copyright notice in the Description page of Project Settings.

#include "NotificationWidgetComponent.h"
#include "UW_Notification.h"
#include "MacroLibrary.h"

void UNotificationWidgetComponent::BeginPlay()
{
    Super::BeginPlay();
    SetHidden(true);
}

void UNotificationWidgetComponent::Notification(FText Text, float Time)
{
    SetHidden(false);

    auto TextWidget = Cast<UUW_Notification>(GetWidget());

    if (!TextWidget)
    {
        auto LocalWidgetClass = GetWidgetClass();
        CHECK_FIELD_RETURN(LocalWidgetClass)

        TextWidget = CreateWidget<UUW_Notification>(GetWorld(), LocalWidgetClass);
        SetWidget(TextWidget);
    }

    CHECK_FIELD_RETURN(TextWidget)
    TextWidget->SetText(Text);

    auto World = GetWorld();
    if (!World)
        return;

    World->GetTimerManager().ClearTimer(Timer);
    World->GetTimerManager().SetTimer(Timer, [this]() { SetHidden(true); }, Time, false);
}

void UNotificationWidgetComponent::SetHidden(bool NewHidden)
{
    SetHiddenInGame(NewHidden);
}
