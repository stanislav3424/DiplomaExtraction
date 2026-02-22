// Fill out your copyright notice in the Description page of Project Settings.

#include "AutoWidgetComponent.h"
#include "HealthLogic.h"
#include "LogicLibrary.h"
#include "MacroLibrary.h"
#include "ExfilGameMode.h"

void UAutoWidgetComponent::BeginPlay()
{
    auto GameMode = AExfilGameMode::Get(GetWorld());
    CHECK_VAR_RETURN(GameMode);

    GameMode->OnStatusGameChanged.AddUniqueDynamic(this, &UAutoWidgetComponent::OnStatusGameChanged);
    OnStatusGameChanged(GameMode->GetStatusGame());
}

ULogicBase* UAutoWidgetComponent::GetLogic_Implementation()
{
    return LogicBase;
}

void UAutoWidgetComponent::SetLogic_Implementation(ULogicBase* NewLogic)
{
    LogicBase = NewLogic;
    if (!LogicBase)
        return;
    auto WidgetLocal = Cast<UUserWidget>(GetUserWidgetObject());
    if (!WidgetLocal && WidgetClass && GetWorld())
    {
        WidgetLocal = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
        if (WidgetLocal)
            SetWidget(WidgetLocal);
    }
    CHECK_VAR_RETURN(WidgetLocal);
    ULogicLibrary::SetLogic(WidgetLocal, LogicBase);

    auto HealthLogic = UHealthLogic::GetHealthLogic_Logic(LogicBase);
    CHECK_VAR_RETURN(HealthLogic);

    HealthLogic->OnDeath.AddUniqueDynamic(this, &UAutoWidgetComponent::Death);
}

void UAutoWidgetComponent::Death()
{
    auto HealthLogic = UHealthLogic::GetHealthLogic_Logic(LogicBase);
    CHECK_VAR_RETURN(HealthLogic);

    HealthLogic->OnDeath.RemoveAll(this);

    DestroyComponent();
}

void UAutoWidgetComponent::OnStatusGameChanged(EStatusGame const& NewStatusGame)
{
    SetHiddenInGame(NewStatusGame == EStatusGame::Started ? false : true);
}
