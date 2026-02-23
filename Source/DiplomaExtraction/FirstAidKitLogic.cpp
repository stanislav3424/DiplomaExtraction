// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstAidKitLogic.h"
#include "Row.h"
#include "MacroLibrary.h"
#include "HealthLogic.h"

void UFirstAidKitLogic::InitializeRowHandler(FDataTableRowHandle const& InitRowHandle)
{
    Super::InitializeRowHandler(InitRowHandle);

    auto Row = InitRowHandle.GetRow<FFirstAidKitRow>(FILE_FUNC);
    if (!Row)
        return;

    Heal = Row->Heal;
    InitializeFirstAidKit();
}

void UFirstAidKitLogic::InitializeFirstAidKit()
{
    if (Heal <= 0)
    {
        Heal = 100.f;
        UE_LOG(InitGameLogic, Warning, FILE_FUNC TEXT("Heal was invalid, resetting to default (100.0)"));
    }
}

void UFirstAidKitLogic::Apply()
{
    auto Inventory = GetOwnerLogic();
    if (!Inventory)
        return;

    auto CharacterLogic = Inventory->GetOwnerLogic();
    if (!CharacterLogic)
        return;

    auto HealthLogic = CharacterLogic->GetLogicComponent<UHealthLogic>();
    if (!HealthLogic)
        return;

    HealthLogic->Heal(Heal);

    OnHealingEnd.Broadcast();
    OnHealingEnd.Clear();

    auto LocalOwnerLogic = GetOwnerLogic();
    if (LocalOwnerLogic)
        RemoveLogicComponent(this);
}
