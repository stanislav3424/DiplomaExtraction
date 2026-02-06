// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UW_Base.h"
#include "UW_Equipment.generated.h"

class UUW_Item;
enum class EEquipmentSlot : uint8;

UCLASS(Abstract, Blueprintable)
class DIPLOMAEXTRACTION_API UUW_Equipment : public UUW_Base
{
    GENERATED_BODY()

    UUW_Equipment();

protected:
    virtual void LogicChanged(ULogicBase* OldLogic, ULogicBase* NewLogic);
    virtual bool NativeOnDrop(
        const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

    UPROPERTY(meta = (BindWidget))
    UUW_Item* ItemWidget;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EquipmentSlot")
    EEquipmentSlot EquipmentSlot;

    UFUNCTION()
    void OnEquipmentChanged();
};
