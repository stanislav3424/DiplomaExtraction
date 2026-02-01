// Fill out your copyright notice in the Description page of Project Settings.

#include "ExfilHUD.h"
#include "UMG.h"
#include "MacroLibrary.h"
#include "LogicLibrary.h"
#include "UW_Dialog.h" 

void AExfilHUD::BeginPlay()
{
    Super::BeginPlay();

    CHECK_FIELD_RETURN(MainMenuWidgetClass) 
    CHECK_FIELD_RETURN(InventoryWidgetClass)

    MainMenuWidget = CreateWidget<UUW_Dialog>(GetWorld(), MainMenuWidgetClass);
    if (!MainMenuWidget) 
        return;
    MainMenuWidget->AddToViewport(0);

    InventoryWidget = CreateWidget<UUW_Dialog>(GetWorld(), InventoryWidgetClass);
    if (!InventoryWidget)
        return;
    InventoryWidget->AddToViewport(-1);

    auto PlayerLogic = ULogicLibrary::GetLogic(GetOwningPlayerController());
    CHECK_FIELD_RETURN(PlayerLogic)
    ULogicLibrary::SetLogic(InventoryWidget, PlayerLogic);
}

void AExfilHUD::ToggleMainMenu()
{
    if (MainMenuWidget)
        MainMenuWidget->ToggleDialog();
}

void AExfilHUD::ToggleInventory()
{
    if (InventoryWidget)
        InventoryWidget->ToggleDialog();
}
