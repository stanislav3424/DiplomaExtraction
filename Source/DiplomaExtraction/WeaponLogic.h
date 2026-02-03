// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LogicBase.h"
#include "WeaponLogic.generated.h"

UCLASS(NotBlueprintable)
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
    void         StartFiring();
    void         StopFiring();

private:
    float GetRateOfFireOneSecond() const;
    float GetFireDelay() const;
    void  Shoot();
    FVector GetMuzzleLocation() const;
    FVector GetShootDirection() const;

private:
    float Damage     = 35.f;
    float RateOfFire = 600.f;
    float Ammo       = 30.f;

    float CurrentAmmo = 30.f;
    float FireDelay   = 1.f;

    float TimeSinceLastShot = 0.f;
    bool  bIsFiring         = false;
};
