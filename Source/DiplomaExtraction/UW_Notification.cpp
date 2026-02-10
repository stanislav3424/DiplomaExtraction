// Fill out your copyright notice in the Description page of Project Settings.

#include "UW_Notification.h"
#include "Components/TextBlock.h"

void UUW_Notification::SetText(FText Text)
{
    if (TextWidget)
        TextWidget->SetText(Text);
}
