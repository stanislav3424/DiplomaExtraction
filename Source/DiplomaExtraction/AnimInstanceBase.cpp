// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimInstanceBase.h"
#include "CharacterLogic.h"
#include "LogicLibrary.h"
#include "SpawnLibrary.h"

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
        Speed  = Pawn->GetVelocity().Size();
        Rotate = Pawn->GetActorRotation().Yaw - Pawn->GetVelocity().Rotation().Yaw;
    }

    if (CharacterLogic->GetEquippedItem(EEquipmentSlot::Hands))
        bIsWeaponEquipped = true;
    else
        bIsWeaponEquipped = false;
}