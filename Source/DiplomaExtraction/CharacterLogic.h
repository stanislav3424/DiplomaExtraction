// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LogicBase.h"
#include "CharacterLogic.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEquipmentChanged);

enum class EEquipmentSlot : uint8;

UENUM(BlueprintType)
enum class ETypeAction : uint8
{
    Idle      UMETA(DisplayName = "Idle"),
    Firing    UMETA(DisplayName = "Firing"),
    Reloading UMETA(DisplayName = "Reloading"),
    Runing    UMETA(DisplayName = "Runing"),
};

class UEquipmentLogic;

UCLASS(Blueprintable)
class DIPLOMAEXTRACTION_API UCharacterLogic : public ULogicBase
{
    GENERATED_BODY()

    // Initialize
public:
    virtual void InitializeRowHandler(FDataTableRowHandle const& InitRowHandle);
    virtual void RemoveChildLogic(ULogicBase* ChildLogic);
    virtual void OnGround();
    virtual void SetSimulatePhysics();

protected:
    virtual void RepresentationActorChanged(AActor* NewRepresentationActor) override;
    virtual void AttachedComponent(ULogicBase* NewComponent) override;

    // Equipment Management
public:
    bool                    EquipItem(ULogicBase* Item);
    UFUNCTION(BlueprintCallable)
    bool                    EquipItem(EEquipmentSlot const& TargetSlot, ULogicBase* Item);
    void                    SetVisualization(const EEquipmentSlot& TargetSlot, ULogicBase* Item);
    bool                    CanEquipItem(EEquipmentSlot const& TargetSlot, ULogicBase* Item);
    ULogicBase*             UnequipItem(ULogicBase* Item);
    ULogicBase*             UnequipItem(EEquipmentSlot const& TargetSlot);
    UFUNCTION(BlueprintCallable)
    ULogicBase*             GetEquippedItem(EEquipmentSlot const& TargetSlot) const;
    bool                    IsValidEquippedItem(ULogicBase* Item);
    static EEquipmentSlot   GetEquipmentSlot(ULogicBase* Item);

    FOnEquipmentChanged OnEquipmentChanged;

private:
    UPROPERTY(Transient)
    TMap<EEquipmentSlot, ULogicBase*> EquippedItems;

    // Control
public:
    UFUNCTION(BlueprintCallable)
    void OnShift(bool bShift);

    UFUNCTION(BlueprintCallable)
    void OnShoot(bool bShoot);

    UFUNCTION(BlueprintCallable)
    void OnReload();

private:
    ETypeAction TypeAction = ETypeAction::Idle;
    bool        ToСhangeTypeAction(ETypeAction const& NewTypeAction);

    UFUNCTION()
    void        ResetTypeAction();
};
