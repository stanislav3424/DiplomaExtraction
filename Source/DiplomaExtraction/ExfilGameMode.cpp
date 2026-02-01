// Fill out your copyright notice in the Description page of Project Settings.

#include "ExfilGameMode.h"
#include "IconRendering.h"

void AExfilGameMode::BeginPlay()
{
    Super::BeginPlay();

    auto World = GetWorld();
    if (!World)
        return;

    IconRenderer = World->SpawnActor<AIconRendering>(IconRendererClass);
}
