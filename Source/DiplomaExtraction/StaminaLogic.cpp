// Fill out your copyright notice in the Description page of Project Settings.

#include "StaminaLogic.h"
#include "SpawnLibrary.h"
#include "MacroLibrary.h"

void UStaminaLogic::InitializeRowHandler(FDataTableRowHandle const& InitRowHandle)
{
    Super::InitializeRowHandler(InitRowHandle);

    auto Row = InitRowHandle.GetRow<FStaminaLogicRow>(FILE_FUNC);
    if (!Row)
        return;

    MaxStamina = Row->MaxStamina;
}

void UStaminaLogic::SetOwnerLogic(ULogicBase* IntOwnerLogic)
{
    Super::SetOwnerLogic(IntOwnerLogic);
    CurrentStamina = MaxStamina;
}

void UStaminaLogic::ConsumeStamina(float Amount)
{
    if (Amount <= 0.0f)
        return;

    CurrentStamina = FMath::Max(0.0f, CurrentStamina - Amount);
    BroadcastStaminaChanged();
}

void UStaminaLogic::RestoreStamina(float Amount)
{
    if (Amount <= 0.0f)
        return;

    CurrentStamina = FMath::Min(CurrentStamina + Amount, MaxStamina);
    BroadcastStaminaChanged();
}
