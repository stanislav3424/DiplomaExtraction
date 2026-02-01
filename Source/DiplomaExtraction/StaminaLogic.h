#pragma once

#include "CoreMinimal.h"
#include "LogicBase.h"
#include "StaminaLogic.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStaminaChanged, float, CurrentStamina, float, MaxStamina);

UCLASS(Blueprintable)
class DIPLOMAEXTRACTION_API UStaminaLogic : public ULogicBase
{
    GENERATED_BODY()

    UStaminaLogic();

    // Initialize
public:
    virtual void InitializeRowHandler(FDataTableRowHandle const& InitRowHandle) override;

    // Components
public:
    virtual void SetOwnerLogic(ULogicBase* IntOwnerLogic) override;

    // Health Management
public:
    float GetStamina() const { return CurrentStamina; }
    float GetMaxStamina() const { return MaxStamina; }

    FOnStaminaChanged OnStaminaChanged;

    void BroadcastStaminaChanged() const { OnStaminaChanged.Broadcast(CurrentStamina, MaxStamina); }

private:
    float MaxStamina             = 100.0f;
    float CurrentStamina         = 100.f;
    float MinStaminaToRun        = 20.0f;
    float StaminaConsumptionRate = 10.0f;
    float StaminaRegenRate       = 5.0f;

    float WalkSpeed = 300.0f;
    float RunSpeed  = 600.0f;

    bool bIsRunning = false;
    bool bCanRun    = false;

    void SetRunning(bool bNewRunning);

public:
    void SetCanRunning(bool bNewCanRun) { bCanRun = bNewCanRun; }

    virtual void Tick(float DeltaTime) override;

private:
    void ConsumeStamina(float DeltaTime);
    void RegenerateStamina(float DeltaTime);
    void CheckRunningState();
};
