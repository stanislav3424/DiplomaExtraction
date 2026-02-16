// Fill out your copyright notice in the Description page of Project Settings.

#include "AutoWidgetComponent.h"
#include "HealthLogic.h"
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
    auto WidgetLocal = Cast<UUserWidget>(GetUserWidgetObject());
    if (!WidgetLocal && WidgetClass && GetWorld())
    {
        WidgetLocal = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
        if (WidgetLocal)
            SetWidget(WidgetLocal);
    }
    CHECK_FIELD_RETURN(WidgetLocal);
    ULogicLibrary::SetLogic(WidgetLocal, LogicBase);

    auto HealthLogic = UHealthLogic::GetHealthLogic_Logic(LogicBase);
    CHECK_FIELD_RETURN(HealthLogic);

    HealthLogic->OnDeath.AddUniqueDynamic(this, &UAutoWidgetComponent::Death);
}

void UAutoWidgetComponent::Death()
{
    DestroyComponent();
}
