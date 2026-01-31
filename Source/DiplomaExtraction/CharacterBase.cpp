// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterBase.h"

ULogicBase* ACharacterBase::GetLogic_Implementation()
{
	return Logic;
}

void ACharacterBase::SetLogic_Implementation(ULogicBase* NewLogic)
{
	Logic = NewLogic;
}
