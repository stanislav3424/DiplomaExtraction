// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugLibrary.h"

void UDrawDebugLibrary::DrawShoot(
    UObject* WorldContextObject, FVector const& Start, FVector const& End, bool bHit, FVector const& HitLocation)
{
#if WITH_EDITOR
    if (!WorldContextObject)
        return;

    if (!GEngine)
        return;

    auto World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
    if (!World)
        return;

    if (bHit)
    {
        DrawShootHitLocation(WorldContextObject, HitLocation);
        DrawDebugLine(World, Start, HitLocation, FColor::Green, false, 1.0f, 0, 1.0f);
        DrawDebugLine(World, HitLocation, End, FColor::Red, false, 1.0f, 0, 1.0f);
    }
    else
    {
        DrawDebugLine(World, Start, End, FColor::Green, false, 1.0f, 0, 1.0f);
    }
#endif
}

void UDrawDebugLibrary::DrawShootHitLocation(UObject* WorldContextObject, FVector const& HitLocation)
{
#if WITH_EDITOR
    if (!WorldContextObject)
        return;

    if (!GEngine)
        return;

    auto World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);
    if (!World)
        return;

    DrawDebugPoint(World, HitLocation, 10.f, FColor::Yellow, false, 1.0f);
#endif
}
