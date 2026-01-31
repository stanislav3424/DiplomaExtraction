// Fill out your copyright notice in the Description page of Project Settings.

#include "UW_Base.h"

ULogicBase* UUW_Base::GetLogic_Implementation()
{
    return Logic;
}

void UUW_Base::SetLogic_Implementation(ULogicBase* NewLogic)
{
    LogicChanged(Logic, NewLogic);
}

void UUW_Base::LogicChanged(ULogicBase* OldLogic, ULogicBase* NewLogic)
{
    Logic = NewLogic;
}
