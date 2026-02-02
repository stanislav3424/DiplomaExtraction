// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthLogic.h"
#include "SpawnLibrary.h"
#include "MacroLibrary.h"
#include "Row.h"

void UHealthLogic::InitializeRowHandler(FDataTableRowHandle const& InitRowHandle)
{
	Super::InitializeRowHandler(InitRowHandle);

	auto HealthRow = InitRowHandle.GetRow<FHealthLogicRow>(FILE_FUNC);
	if (!HealthRow)
		return;

    MaxHealth = HealthRow->MaxHealth;
}

void UHealthLogic::SetOwnerLogic(ULogicBase* IntOwnerLogic)
{
	Super::SetOwnerLogic(IntOwnerLogic);

	CurrentHealth = MaxHealth;
}

void UHealthLogic::TakeDamage(float DamageAmount)
{
	if (DamageAmount > 0.0f)
	{
		CurrentHealth = FMath::Max(0.0f, CurrentHealth - DamageAmount);
        BroadcastHealthChanged();

		if (CurrentHealth <= 0.0f)
		{
			OnDeath.Broadcast();
		}
	}
}

void UHealthLogic::Heal(float HealAmount)
{
	if (HealAmount > 0.0f)
	{
		CurrentHealth = FMath::Min(CurrentHealth + HealAmount, MaxHealth);
        BroadcastHealthChanged();
	}
}
