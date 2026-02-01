// Fill out your copyright notice in the Description page of Project Settings.

#include "UW_HealthProgressBar.h"
#include "HealthLogic.h"
#include "MacroLibrary.h"

void UUW_HealthProgressBar::LogicChanged(ULogicBase* OldLogic, ULogicBase* NewLogic)
{
    Super::LogicChanged(OldLogic, NewLogic);

    if (OldLogic)
        if (auto HealthLogic = OldLogic->GetLogicComponent<UHealthLogic>())
            HealthLogic->OnHealthChanged.RemoveDynamic(this, &UUW_HealthProgressBar::SetPercent);

    if (NewLogic)
    {
        auto HealthLogic = NewLogic->GetLogicComponent<UHealthLogic>();
        CHECK_FIELD_RETURN(HealthLogic);
        HealthLogic->OnHealthChanged.AddUniqueDynamic(this, &UUW_HealthProgressBar::SetPercent);
        HealthLogic->BroadcastHealthChanged();
    }
}
