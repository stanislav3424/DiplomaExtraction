// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "NotificationWidgetComponent.generated.h"

UCLASS(NotBlueprintable, ClassGroup = "UserInterface",
    hidecategories = (Object, Activation, "Components|Activation", Sockets, Base, Lighting, LOD, Mesh), editinlinenew,
    meta           = (BlueprintSpawnableComponent))
class DIPLOMAEXTRACTION_API UNotificationWidgetComponent : public UWidgetComponent
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;
    void Notification(FText Text, float Time);
    void SetHidden(bool NewHidden);

    FTimerHandle Timer;
};
