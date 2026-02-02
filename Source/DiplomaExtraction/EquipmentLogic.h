// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LogicBase.h"
#include "EquipmentLogic.generated.h"

enum class EEquipmentSlot : uint8;

UCLASS(Abstract, NotBlueprintable)
class DIPLOMAEXTRACTION_API UEquipmentLogic : public ULogicBase
{
    GENERATED_BODY()

    UEquipmentLogic();
    // Initialize
public:
    virtual void InitializeRowHandler(FDataTableRowHandle const& InitRowHandle);

    // Item Management
public:
    EEquipmentSlot const& GetEquipmentSlot() const;

private:
    EEquipmentSlot EquipmentSlot;
};
