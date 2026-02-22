// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LogicBase.h"
#include "WeaponLogic.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAmmoEmpty);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEndReloading);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartFiring);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStopFiring);

class UNiagaraSystem;

UCLASS(Blueprintable)
class DIPLOMAEXTRACTION_API UWeaponLogic : public ULogicBase
{
	GENERATED_BODY()

    UWeaponLogic();

    // Initialize
public:
    virtual void InitializeRowHandler(FDataTableRowHandle const& InitRowHandle) override;

    // Components
protected:
    virtual void OwnerLogicChange(ULogicBase* OldOwnerLogic, ULogicBase* NewOwnerLogic) override;

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

    FOnStartFiring OnStartFiring;
    FOnStopFiring  OnStopFiring;

    UFUNCTION(BlueprintCallable)
    static UWeaponLogic* GetEquippedWeaponLogic_Actor(AActor* Actor);
    
    UFUNCTION(BlueprintCallable)
    static UWeaponLogic* GetEquippedWeaponLogic_Logic(ULogicBase* Logic);

private:
    UFUNCTION()
    void    EndReload();
    float   GetRateOfFireOneSecond() const;
    float   GetFireDelay() const;
    void    Shoot();
    FVector GetStartShootLocation() const;
    FVector GetMuzzleLocation() const;
    FVector GetShootDirection() const;
    void    DrawShoot(FVector const& Start, FVector const& End);
    void    PlaySound();

private:
    float Damage     = 35.f;
    float RateOfFire = 600.f;
    int32 Ammo       = 30;

    int32 CurrentAmmo = 30;
    float FireDelay   = 1.f;

    float TimeSinceLastShot = 0.f;
    bool  bIsFiring         = false;

    void SetFiring(bool bNewFiring);

    UPROPERTY(Transient)
    UNiagaraSystem* BulletTraceFX;

    UPROPERTY(Transient)
    USoundBase* SoundShoot;

    UPROPERTY(Transient)
    UAnimMontage* ReloadAnimMontage;
};
