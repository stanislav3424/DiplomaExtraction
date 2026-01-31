// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LogicBase.h"
#include "CharacterLogic.generated.h"

enum class EEquipmentSlot : uint8;

class UItemLogic;

UCLASS(Abstract, NotBlueprintable)
class DIPLOMAEXTRACTION_API UCharacterLogic : public ULogicBase
{
    GENERATED_BODY()

    // Initialize
public:
    virtual void InitializeRowHandler(FDataTableRowHandle const& InitRowHandle);

    // Equipment Management
public:
    bool                  EquipItem(ULogicBase* Item);
    bool                  EquipItem(EEquipmentSlot const& TargetSlot, ULogicBase* Item);
    bool                  CanEquipItem(EEquipmentSlot const& TargetSlot, ULogicBase* Item);
    ULogicBase*           UnequipItem(EEquipmentSlot const& TargetSlot);
    ULogicBase*           GetEquippedItem(EEquipmentSlot const& TargetSlot) const;
    bool                  IsValidEquippedItem(ULogicBase* Item);
    static UItemLogic*    GetItemLogicComponent(ULogicBase* Item);
    static EEquipmentSlot GetEquipmentSlot(ULogicBase* Item);

private:
    TMap<EEquipmentSlot, ULogicBase*> EquippedItems;
};
