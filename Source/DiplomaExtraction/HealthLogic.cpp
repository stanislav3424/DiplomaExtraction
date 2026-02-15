// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthLogic.h"
#include "SpawnLibrary.h"
#include "MacroLibrary.h"
#include "Row.h"
#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "CharacterLogic.h"

void UHealthLogic::InitializeRowHandler(FDataTableRowHandle const& InitRowHandle)
{
	Super::InitializeRowHandler(InitRowHandle);

	auto HealthRow = InitRowHandle.GetRow<FHealthLogicRow>(FILE_FUNC);
	if (!HealthRow)
		return;

    MaxHealth = HealthRow->MaxHealth;
}

void UHealthLogic::OwnerLogicChange(ULogicBase* OldOwnerLogic, ULogicBase* NewOwnerLogic)
{
    Super::OwnerLogicChange(OldOwnerLogic, NewOwnerLogic);

    if (OldOwnerLogic)
    {
        OldOwnerLogic->OnRepresentationActorChanged.RemoveDynamic(
            this, &UHealthLogic::OnOwnerRepresentationActorChanged);
    }

    CurrentHealth = MaxHealth;

    if (NewOwnerLogic)
    {
        OldOwnerLogic->OnRepresentationActorChanged.AddUniqueDynamic(
            this, &UHealthLogic::OnOwnerRepresentationActorChanged);
    }
}

void UHealthLogic::TakeDamage(float DamageAmount)
{
	if (DamageAmount > 0.0f)
	{
		CurrentHealth = FMath::Max(0.0f, CurrentHealth - DamageAmount);
        BroadcastHealthChanged();

		if (CurrentHealth <= 0.0f)
		{
            Die();
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

void UHealthLogic::BroadcastDeathInfo() const
{
    auto Logic = GetOwnerLogic();
    CHECK_FIELD_RETURN(Logic);

	auto Actor = Logic->GetRepresentationActor();
    CHECK_FIELD_RETURN(Actor);

	OnDeath.Broadcast();
	OnDeathInfo.Broadcast(Logic, Actor);
}

void UHealthLogic::Die()
{
    auto CharacterLogic = Cast<UCharacterLogic>(GetOwnerLogic());
    if (!CharacterLogic)
        return;

    CharacterLogic->SetSimulatePhysics();

    BroadcastDeathInfo();
}

void UHealthLogic::OnOwnerRepresentationActorChanged(AActor* NewRepresentationActor)
{
    if (!IsValid(NewRepresentationActor))
        return;

    NewRepresentationActor->OnTakeAnyDamage.AddDynamic(this, &UHealthLogic::HandleDamage);
}

void UHealthLogic::HandleDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    TakeDamage(Damage);
}