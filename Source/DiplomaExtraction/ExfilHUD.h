// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ExfilHUD.generated.h"

class UUW_Dialog;

UCLASS(Abstract, Blueprintable)
class DIPLOMAEXTRACTION_API AExfilHUD : public AHUD
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUW_Dialog> MainMenuWidgetClass;

    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUW_Dialog> InventoryWidgetClass;

    UPROPERTY(Transient)
    UUW_Dialog* MainMenuWidget;

    UPROPERTY(Transient)
    UUW_Dialog* InventoryWidget;

public:
    void ToggleMainMenu();
    void ToggleInventory();
};
