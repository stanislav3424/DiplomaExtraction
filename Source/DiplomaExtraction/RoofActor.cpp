// Fill out your copyright notice in the Description page of Project Settings.

#include "RoofActor.h"
#include "ExfilGameMode.h"
#include "MacroLibrary.h"

void ARoofActor::BeginPlay()
{
	Super::BeginPlay();

    SetVisibility(false);

    TArray<UPrimitiveComponent*> PrimitiveComponents;
    GetComponents<UPrimitiveComponent>(PrimitiveComponents);
    for (auto PrimitiveComponent : PrimitiveComponents)
    {
        if (!PrimitiveComponent)
            continue;

        PrimitiveComponent->SetVisibility(true, true);
        PrimitiveComponent->SetCastHiddenShadow(true);
    }
	
	auto GameMode = AExfilGameMode::Get(GetWorld());
    CHECK_VAR_RETURN(GameMode);

    GameMode->OnStatusGameChanged.AddUniqueDynamic(this, &ARoofActor::OnStatusGameChanged);
    OnStatusGameChanged(GameMode->GetStatusGame());
}

void ARoofActor::OnStatusGameChanged(EStatusGame const& NewStatusGame)
{
    SetVisibility(
        (NewStatusGame == EStatusGame::NotStarted || NewStatusGame == EStatusGame::Over) ? true : false);
}

void ARoofActor::SetVisibility(bool bNewVisibility)
{
    if (bVisibility == bNewVisibility)
        return;

    bVisibility = bNewVisibility;

    TArray<UPrimitiveComponent*> PrimitiveComponents;
    GetComponents<UPrimitiveComponent>(PrimitiveComponents);
    for (auto PrimitiveComponent : PrimitiveComponents)
    {
        if (!PrimitiveComponent)
            continue;

        PrimitiveComponent->SetHiddenInGame(!bVisibility, true);
    }
}
