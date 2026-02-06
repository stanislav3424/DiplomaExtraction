// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UW_Base.h"
#include "UW_GroundLootAdapterWidget.generated.h"

class UInventoryLogic;
class UGroundLootInventoryLogic;

UCLASS(Abstract, Blueprintable)
class DIPLOMAEXTRACTION_API UUW_GroundLootAdapterWidget : public UUW_Base
{
    GENERATED_BODY()

    UUW_GroundLootAdapterWidget();

protected:
    virtual void LogicChanged(ULogicBase* OldLogic, ULogicBase* NewLogic);

    UPROPERTY(Transient)
    UGroundLootInventoryLogic* GroundLootInventoryLogic;
};
