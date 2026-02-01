// Fill out your copyright notice in the Description page of Project Settings.

#include "UW_StaminaProgressBar.h"
#include "StaminaLogic.h"
#include "MacroLibrary.h"

void UUW_StaminaProgressBar::LogicChanged(ULogicBase* OldLogic, ULogicBase* NewLogic)
{
    Super::LogicChanged(OldLogic, NewLogic);

	if (OldLogic)
        if (auto StaminaLogic = OldLogic->GetLogicComponent<UStaminaLogic>())
            StaminaLogic->OnStaminaChanged.RemoveDynamic(this, &UUW_StaminaProgressBar::SetPercent);

    if (NewLogic)
    {
        auto StaminaLogic = NewLogic->GetLogicComponent<UStaminaLogic>();
        CHECK_FIELD_RETURN(StaminaLogic);
        StaminaLogic->OnStaminaChanged.AddUniqueDynamic(this, &UUW_StaminaProgressBar::SetPercent);
        StaminaLogic->BroadcastStaminaChanged();
    }
}
