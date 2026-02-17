// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponLogic.h"
#include "Row.h"
#include "MacroLibrary.h"
#include "LogicLibrary.h"
#include "DrawDebugLibrary.h"
#include "CharacterLogic.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"

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

    Damage        = Row->Damage;
    RateOfFire    = Row->RateOfFire;
    Ammo          = Row->Ammo;
    BulletTraceFX = Row->BulletTraceFX;
    SoundShoot    = Row->SoundShoot;

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

    CHECK_VAR(BulletTraceFX);
    CHECK_VAR(SoundShoot);

    CurrentAmmo = Ammo;
    FireDelay   = GetFireDelay();
}

void UWeaponLogic::TickLogic(float DeltaTime)
{
    Super::TickLogic(DeltaTime);

    TimeSinceLastShot += DeltaTime;

    if (CurrentAmmo <= 0)
    {
        bIsFiring = false;
        return;
    }

    if (bIsFiring && TimeSinceLastShot >= FireDelay)
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
    CurrentAmmo = Ammo;
    OnEndReloading.Broadcast();
}

UWeaponLogic* UWeaponLogic::GetEquippedWeaponLogic_Actor(AActor* Actor)
{
    return GetEquippedWeaponLogic_Logic(ULogicLibrary::GetLogic(Actor));
}

UWeaponLogic* UWeaponLogic::GetEquippedWeaponLogic_Logic(ULogicBase* Logic)
{
    auto CharacterLogic = Cast<UCharacterLogic>(Logic);
    if (!CharacterLogic)
        return nullptr;

    auto WeaponLogic = Cast<UWeaponLogic>(CharacterLogic->GetEquippedItem(EEquipmentSlot::Hands));
    if (!WeaponLogic)
        return nullptr;

    return WeaponLogic;
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
    float                 Range   = 5000.f;
    FVector               End     = Start + Forward * Range;
    FHitResult            HitResult;
    FCollisionQueryParams CollisionQueryParams;

    auto LocalLogic = GetOwnerLogic();
    if (!LocalLogic)
        return;

    auto LocalActor = LocalLogic->GetRepresentationActor();
    if (!LocalActor)
        return;

    CollisionQueryParams.AddIgnoredActor(GetRepresentationActor());
    CollisionQueryParams.AddIgnoredActor(LocalActor);

    World->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionQueryParams);

    if (HitResult.bBlockingHit)
    {
        UGameplayStatics::ApplyDamage(HitResult.GetActor(), Damage, nullptr, nullptr, UDamageType::StaticClass());
    }

    DrawShoot(Start, HitResult.bBlockingHit ? HitResult.Location : End);
    UDrawDebugLibrary::DrawShoot(World, Start, End, HitResult.bBlockingHit, HitResult.Location);


    PlaySound();
    

    if (CurrentAmmo <= 0)
    {
        bIsFiring = false;
        OnAmmoEmpty.Broadcast();
    }
}

FVector UWeaponLogic::GetMuzzleLocation() const
{
    FVector Location = FVector(0.f, 0.f, 45.f);

    auto CharacterLogic = Cast<UCharacterLogic>(GetOwnerLogic());
    if (!CharacterLogic)
        return Location;

    auto Character = Cast<ACharacter>(CharacterLogic->GetRepresentationActor());
    if (!Character)
        return Location;

    Location += Character->GetActorLocation();
    //auto Mesh = Character->GetMesh();
    //if (!Mesh)
    //    return Location;

    //Location = Mesh->GetSocketLocation(TEXT("weapon_r_muzzle"));

    return Location;
}

FVector UWeaponLogic::GetShootDirection() const
{
    FVector Location = FVector::ZeroVector;

    auto CharacterLogic = Cast<UCharacterLogic>(GetOwnerLogic());
    if (!CharacterLogic)
        return Location;

    auto Actor = CharacterLogic->GetRepresentationActor();
    if (!Actor)
        return Location;

    Location = Actor->GetActorRotation().Vector();

    return Location;
}

void UWeaponLogic::DrawShoot(FVector const& Start, FVector const& End)
{
    CHECK_VAR_RETURN(BulletTraceFX)

    const float Speed    = 7000.f;
    const float Distance = FVector::Distance(Start, End);
    const float LifeTime = Distance / Speed;
    FRotator    Rotation = (End - Start).Rotation();

    auto NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), BulletTraceFX, Start, Rotation);
    if (!NiagaraComponent)
        return;

    NiagaraComponent->SetFloatParameter(TEXT("User.Lifatime"), LifeTime);
    NiagaraComponent->SetFloatParameter(TEXT("User.Speed"), Speed);
}

void UWeaponLogic::PlaySound()
{
    if (!SoundShoot)
        return;

    auto LocalLogic = GetOwnerLogic();
    if (!LocalLogic)
        return;

    auto LocalActor = LocalLogic->GetRepresentationActor();
    if (!LocalActor)
        return;

    USoundAttenuation*         Attenuation = NewObject<USoundAttenuation>(USoundAttenuation::StaticClass());
    FSoundAttenuationSettings& Settings    = Attenuation->Attenuation;
    Settings.bAttenuate                    = true;
    Settings.bSpatialize                   = true;
    Settings.AttenuationShape              = EAttenuationShape::Sphere;
    Settings.AttenuationShapeExtents       = FVector(0.f);
    Settings.FalloffDistance               = 2000.f;
    UGameplayStatics::PlaySoundAtLocation(this, SoundShoot, LocalActor->GetActorLocation(), 1.f, 1.f, 0.f, Attenuation);
}