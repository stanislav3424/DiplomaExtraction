// Fill out your copyright notice in the Description page of Project Settings.

#include "StaminaLogic.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SpawnLibrary.h"
#include "MacroLibrary.h"
#include "Row.h"

UStaminaLogic::UStaminaLogic()
{
    bIsTickEnabled = true;
}

void UStaminaLogic::InitializeRowHandler(FDataTableRowHandle const& InitRowHandle)
{
    Super::InitializeRowHandler(InitRowHandle);

    auto Row = InitRowHandle.GetRow<FStaminaLogicRow>(FILE_FUNC);
    if (!Row)
        return;

    MaxStamina = Row->MaxStamina;
}

void UStaminaLogic::OwnerLogicChange(ULogicBase* OldOwnerLogic, ULogicBase* NewOwnerLogic)
{
    Super::OwnerLogicChange(OldOwnerLogic, NewOwnerLogic);

    CurrentStamina = MaxStamina;

    OnStaminaChanged.Clear();
    OnStartRun.Clear();
    OnEndRun.Clear();

    if (NewOwnerLogic)
        NewOwnerLogic->OnRepresentationActorChanged.AddUniqueDynamic(
            this, &UStaminaLogic::OnRepresentationActorChanged);
}

void UStaminaLogic::OnRepresentationActorChanged(AActor* NewRepresentationActor)
{
    ApplyRunning();
}

void UStaminaLogic::SetRunning(bool bNewRunning)
{
    if (bIsRunning == bNewRunning)
        return;

    bIsRunning = bNewRunning;

    ApplyRunning();

    if (bIsRunning)
        OnStartRun.Broadcast();
    else
        OnEndRun.Broadcast();
}

void UStaminaLogic::ApplyRunning()
{
    auto Logic = GetOwnerLogic();
    if (!Logic)
        return;

    auto Character = Cast<ACharacter>(Logic->GetRepresentationActor());
    CHECK_VAR_RETURN(Character)

    auto Movement = Character->GetCharacterMovement();
    CHECK_VAR_RETURN(Movement)

    Movement->MaxWalkSpeed = bIsRunning ? RunSpeed : WalkSpeed;
}

void UStaminaLogic::TickLogic(float DeltaTime)
{
    if (!GetOwnerLogic())
        return;

    ConsumeStamina(DeltaTime);
    RegenerateStamina(DeltaTime);
    CheckRunningState();
}

void UStaminaLogic::ConsumeStamina(float DeltaTime)
{
    if (!bIsRunning)
        return;

    CurrentStamina = FMath::Max(0.0f, CurrentStamina - StaminaConsumptionRate * DeltaTime);
    BroadcastStaminaChanged();
}

void UStaminaLogic::RegenerateStamina(float DeltaTime)
{
    if (bIsRunning)
        return;
    if (CurrentStamina < MaxStamina)
    {
        CurrentStamina = FMath::Min(MaxStamina, CurrentStamina + StaminaRegenRate * DeltaTime);
        BroadcastStaminaChanged();
    }
}

void UStaminaLogic::CheckRunningState()
{
    if (!bCanRun)
    {
        SetRunning(false);
        return;
    }

    if (bIsRunning)
        if (CurrentStamina <= 0.f)
             SetRunning(false);

    if (!bIsRunning)
        if (CurrentStamina > MinStaminaToRun)
             SetRunning(true);
}
