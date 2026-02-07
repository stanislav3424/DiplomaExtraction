// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryLogic.h"
#include "GroundLootInventoryLogic.generated.h"

UCLASS(NotBlueprintable)
class DIPLOMAEXTRACTION_API UGroundLootInventoryLogic : public UInventoryLogic
{
    GENERATED_BODY()

public:
    void InitSize();

public:
    virtual bool CanAddItemToPosition(
        ULogicBase* Item, FIntVector2 const& Position, bool Rotation = false) override final;

protected:
    virtual void PlaceItemInInventory(ULogicBase* Item, FIntVector2 const& Position, bool Rotation = false,
        bool bAddLogicComponent = true) override final;
};
