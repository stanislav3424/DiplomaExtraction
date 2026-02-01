// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterBase.h"

ULogicBase* ACharacterBase::GetLogic_Implementation()
{
    return LogicBase;
}

void ACharacterBase::SetLogic_Implementation(ULogicBase* NewLogic)
{
    LogicBase = NewLogic;
}
