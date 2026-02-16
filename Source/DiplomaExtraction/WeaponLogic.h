// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LogicBase.h"
#include "WeaponLogic.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAmmoEmpty);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndReloading);

UCLASS(Blueprintable)
class DIPLOMAEXTRACTION_API UWeaponLogic : public ULogicBase
{
	GENERATED_BODY()

    UWeaponLogic();

    // Initialize
public:
    virtual void InitializeRowHandler(FDataTableRowHandle const& InitRowHandle) override;

private:
    void InitializeWeapon();

    // Weapon Functionality
public:
    virtual void TickLogic(float DeltaTime);

    UFUNCTION(BlueprintCallable)
    void StartFiring();

    UFUNCTION(BlueprintCallable)
    void StopFiring();

    UFUNCTION(BlueprintCallable)
    void Reload();

    UPROPERTY(BlueprintAssignable)
    FOnAmmoEmpty OnAmmoEmpty;

    UPROPERTY(BlueprintAssignable)
    FOnEndReloading OnEndReloading;

    UFUNCTION(BlueprintCallable)
    static UWeaponLogic* GetEquippedWeaponLogic_Actor(AActor* Actor);
    
    UFUNCTION(BlueprintCallable)
    static UWeaponLogic* GetEquippedWeaponLogic_Logic(ULogicBase* Logic);

private:
    float GetRateOfFireOneSecond() const;
    float GetFireDelay() const;
    void  Shoot();
    FVector GetMuzzleLocation() const;
    FVector GetShootDirection() const;

private:
    float Damage     = 35.f;
    float RateOfFire = 600.f;
    int32 Ammo       = 30;

    int32 CurrentAmmo = 30;
    float FireDelay   = 1.f;

    float TimeSinceLastShot = 0.f;
    bool  bIsFiring         = false;
};
