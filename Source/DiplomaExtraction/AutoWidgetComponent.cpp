// Fill out your copyright notice in the Description page of Project Settings.

#include "AutoWidgetComponent.h"
#include "LogicLibrary.h"
#include "MacroLibrary.h"

ULogicBase* UAutoWidgetComponent::GetLogic_Implementation()
{
    return LogicBase;
}

void UAutoWidgetComponent::SetLogic_Implementation(ULogicBase* NewLogic)
{
    LogicBase = NewLogic;
    if (!LogicBase)
        return;
    auto WidgetLocal = GetWidget();
    CHECK_FIELD_RETURN(WidgetLocal);
    ULogicLibrary::SetLogic(WidgetLocal, LogicBase);
}
