// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponLogic.h"
#include "Row.h"
#include "MacroLibrary.h"
#include "DrawDebugLibrary.h"

UWeaponLogic::UWeaponLogic()
{
    bIsTickEnabled = true;
}

void UWeaponLogic::InitializeRowHandler(FDataTableRowHandle const& InitRowHandle)
{
    Super::InitializeRowHandler(InitRowHandle);

    auto Row = InitRowHandle.GetRow<FWeaponLogicRow>(FILE_FUNC);
    if (!Row)
        return;

    Damage = Row->Damage;
    RateOfFire = Row->RateOfFire;
    Ammo = Row->Ammo;

    InitializeWeapon();
}

void UWeaponLogic::InitializeWeapon()
{
    if (Damage <= 0)
    {
        Damage = 35.f;
        UE_LOG(InitGameLogic, Warning, FILE_FUNC TEXT("Damage was invalid, resetting to default (35.0)"));
    }
    if (RateOfFire <= 0)
    {
        RateOfFire = 600.f;
        UE_LOG(InitGameLogic, Warning, FILE_FUNC TEXT("RateOfFire was invalid, resetting to default (600.0)"));
    }
    if (Ammo <= 0)
    {
        Ammo = 30.f;
        UE_LOG(InitGameLogic, Warning, FILE_FUNC TEXT("Ammo was invalid, resetting to default (30.0)"));
    }

    CurrentAmmo = Ammo;
    FireDelay   = GetFireDelay();
}

void UWeaponLogic::TickLogic(float DeltaTime)
{
    Super::TickLogic(DeltaTime);

    TimeSinceLastShot += DeltaTime;

    if (bIsFiring)
        if (TimeSinceLastShot >= FireDelay && CurrentAmmo > 0)
        {
            Shoot();
            TimeSinceLastShot = 0.f;
        }
}

void UWeaponLogic::StartFiring()
{
    bIsFiring = true;
}

void UWeaponLogic::StopFiring()
{
    bIsFiring = false;
}

void UWeaponLogic::Reload()
{
    //
}

float UWeaponLogic::GetRateOfFireOneSecond() const
{
    return RateOfFire / 60.0f;
}

float UWeaponLogic::GetFireDelay() const
{
    return 60.0f / RateOfFire;
}

void UWeaponLogic::Shoot()
{
    if (CurrentAmmo <= 0)
        return;

    CurrentAmmo--;

    auto World = GetWorld();
    if (!World)
        return;

    FVector               Start   = GetMuzzleLocation();
    FVector               Forward = GetShootDirection();
    float                 Range   = 3000.f;
    FVector               End     = Start + Forward * Range;
    FHitResult            HitResult;
    FCollisionQueryParams CollisionQueryParams;
    CollisionQueryParams.AddIgnoredActor(GetRepresentationActor());
    World->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionQueryParams);

    if (HitResult.bBlockingHit)
    {
    }

    UDrawDebugLibrary::DrawShoot(World, Start, End, HitResult.Location);
}

FVector UWeaponLogic::GetMuzzleLocation() const
{
    return FVector();
}

FVector UWeaponLogic::GetShootDirection() const
{
    return FVector();
}
