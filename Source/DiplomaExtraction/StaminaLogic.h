#pragma once

#include "CoreMinimal.h"
#include "LogicBase.h"
#include "StaminaLogic.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStaminaChanged, float, CurrentStamina, float, MaxStamina);

UCLASS(Abstract, NotBlueprintable)
class DIPLOMAEXTRACTION_API UStaminaLogic : public ULogicBase
{
    GENERATED_BODY()

    // Initialize
public:
    virtual void InitializeRowHandler(FDataTableRowHandle const& InitRowHandle) override;

    // Components
public:
    virtual void SetOwnerLogic(ULogicBase* IntOwnerLogic) override;

    // Health Management
public:
    void ConsumeStamina(float Amount);
    void RestoreStamina(float Amount);

    float GetStamina() const { return CurrentStamina; }
    float GetMaxStamina() const { return MaxStamina; }

    FOnStaminaChanged OnStaminaChanged;

    void BroadcastStaminaChanged() const { OnStaminaChanged.Broadcast(CurrentStamina, MaxStamina); }

private:
    float MaxStamina = 100.0f;
    float CurrentStamina;
};
