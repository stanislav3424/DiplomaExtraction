// Fill out your copyright notice in the Description page of Project Settings.

#include "GroundLootInventoryLogic.h"

void UGroundLootInventoryLogic::InitSize()
{
    InitializeInventory(FIntVector2(8, 12));
}

bool UGroundLootInventoryLogic::CanAddItemToPosition(ULogicBase* Item, FIntVector2 const& Position, bool Rotation)
{
    return true;
}

void UGroundLootInventoryLogic::PlaceItemInInventory(ULogicBase* Item, FIntVector2 const& Position, bool Rotation)
{
}
