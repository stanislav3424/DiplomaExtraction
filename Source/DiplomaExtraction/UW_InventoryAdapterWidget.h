// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UW_Base.h"
#include "UW_InventoryAdapterWidget.generated.h"

class UInventoryLogic;

UCLASS(Abstract, Blueprintable)
class DIPLOMAEXTRACTION_API UUW_InventoryAdapterWidget : public UUW_Base
{
	GENERATED_BODY()

	UUW_InventoryAdapterWidget();

protected:
    virtual void LogicChanged(ULogicBase* OldLogic, ULogicBase* NewLogic);

	UFUNCTION()
    void OnEquipmentChanged();

	UPROPERTY(Transient)
	UInventoryLogic* InventoryLogic;
};
