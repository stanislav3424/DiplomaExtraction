// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UW_Base.h"
#include "UW_Inventory.generated.h"

class UUW_Item;
class UCanvasPanel;
class UUW_InventoryGrid;
class USizeBox;

UCLASS(Abstract, Blueprintable)
class DIPLOMAEXTRACTION_API UUW_Inventory : public UUW_Base
{
    GENERATED_BODY()

    UUW_Inventory();

protected:
    virtual void LogicChanged(ULogicBase* OldLogic, ULogicBase* NewLogic);

    UFUNCTION()
    void OnInventoryChanged();

    UPROPERTY(Transient)
    TArray<UUW_Item*> ItemWidgets;

    UPROPERTY(EditDefaultsOnly, Category = "ItemWidgetClass")
    TSubclassOf<UUW_Item> ItemWidgetClass;

    UPROPERTY(meta = (BindWidget))
    UCanvasPanel* CanvasPanel;

    UPROPERTY(meta = (BindWidget))
    UUW_InventoryGrid* InventoryGrid;

    UPROPERTY(meta = (BindWidget))
    USizeBox* SizeBox;
};
