// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimInstanceBase.h"
#include "CharacterLogic.h"
#include "LogicLibrary.h"
#include "SpawnLibrary.h"
#include "Row.h"

void UAnimInstanceBase::NativeBeginPlay()
{
    Super::NativeBeginPlay();

    Pawn = TryGetPawnOwner();
}

void UAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    if (!CharacterLogic)
        CharacterLogic = ULogicLibrary::GetLogic<UCharacterLogic>(TryGetPawnOwner());

    if (!CharacterLogic)
        return;

    if (Pawn)
    {
        Speed = Pawn->GetVelocity().Size();

        bIsIdle = Speed < KINDA_SMALL_NUMBER ? true : false;

        float ActorYaw    = Pawn->GetActorRotation().Yaw;
        float MovementYaw = Pawn->GetVelocity().Rotation().Yaw;
        Rotate            = FMath::FindDeltaAngleDegrees(ActorYaw, MovementYaw);
    }

    if (CharacterLogic->GetEquippedItem(EEquipmentSlot::Hands))
        bIsWeaponEquipped = true;
    else
        bIsWeaponEquipped = false;
}