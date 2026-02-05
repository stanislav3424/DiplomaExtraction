// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LogicBase.h"
#include "SpawnLibrary.h"
#include "HealthLogic.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, CurrentHealth, float, MaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS(Blueprintable)
class DIPLOMAEXTRACTION_API UHealthLogic : public ULogicBase
{
    GENERATED_BODY()

    // Initialize
public:
    virtual void InitializeRowHandler(FDataTableRowHandle const& InitRowHandle) override;

    // Components
public:
    virtual void OwnerLogicChange(ULogicBase* IntOwnerLogic) override;

    // Health Management
    void TakeDamage(float DamageAmount);
    void Heal(float HealAmount);
    float GetHealth() const { return CurrentHealth; }
    float GetMaxHealth() const { return MaxHealth; }
    bool IsAlive() const { return CurrentHealth > 0.0f; }

    FOnHealthChanged OnHealthChanged;
    FOnDeath OnDeath;

    void BroadcastHealthChanged() const { OnHealthChanged.Broadcast(CurrentHealth, MaxHealth); }

private:
    float MaxHealth = 100.0f;
    float CurrentHealth;
};
