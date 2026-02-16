// Fill out your copyright notice in the Description page of Project Settings.

#include "SceneComponentBase.h"

ULogicBase* USceneComponentBase::GetLogic_Implementation()
{
    return LogicBase;
}

void USceneComponentBase::SetLogic_Implementation(ULogicBase* NewLogic)
{
    LogicBase = NewLogic;
}
