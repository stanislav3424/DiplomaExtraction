// Fill out your copyright notice in the Description page of Project Settings.

#include "UW_GroundLootAdapterWidget.h"
#include "InventoryLogic.h"
#include "Row.h"
#include "MacroLibrary.h"
#include "GroundLootInventoryLogic.h"

UUW_GroundLootAdapterWidget::UUW_GroundLootAdapterWidget()
{
    bIsAutoInitializeChildLogic = false;
}

void UUW_GroundLootAdapterWidget::LogicChanged(ULogicBase* OldLogic, ULogicBase* NewLogic)
{
    Super::LogicChanged(OldLogic, NewLogic);

    UGroundLootInventoryLogic* NewGroundLootInventoryLogic =
        Cast<UGroundLootInventoryLogic>(NewLogic->GetLogicComponent<UGroundLootInventoryLogic>());

    if (GroundLootInventoryLogic != NewGroundLootInventoryLogic)
    {
        GroundLootInventoryLogic = NewGroundLootInventoryLogic;
        InitializeChildLogic(GroundLootInventoryLogic);
    }
}
