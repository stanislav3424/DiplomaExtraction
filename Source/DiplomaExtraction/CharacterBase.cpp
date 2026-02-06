// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterBase.h"
#include "InitRowHandle.h"

ACharacterBase::ACharacterBase()
{
    InitRowHandle = CreateDefaultSubobject<UInitRowHandle>(TEXT("InitRowHandle"));
}

ULogicBase* ACharacterBase::GetLogic_Implementation()
{
    return LogicBase;
}

void ACharacterBase::SetLogic_Implementation(ULogicBase* NewLogic)
{
    LogicBase = NewLogic;
}
