// Fill out your copyright notice in the Description page of Project Settings.

#include "NotificationWidgetComponent.h"
#include "UW_Notification.h"
#include "MacroLibrary.h"

void UNotificationWidgetComponent::AddNotification(FText Text, float Time)
{
    auto UW_Notification = Cast<UUW_Notification>(GetWidget());
    CHECK_VAR_RETURN(UW_Notification)
    UW_Notification->AddNotification(Text, Time);
}
