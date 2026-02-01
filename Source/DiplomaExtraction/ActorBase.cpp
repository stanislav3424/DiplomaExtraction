// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorBase.h"

ULogicBase* AActorBase::GetLogic_Implementation()
{
    return LogicBase;
}

void AActorBase::SetLogic_Implementation(ULogicBase* NewLogic)
{
    LogicBase = NewLogic;
}
