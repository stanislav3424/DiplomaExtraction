// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DrawDebugLibrary.generated.h"

UCLASS()
class DIPLOMAEXTRACTION_API UDrawDebugLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    static void DrawShoot(
        UObject* WorldContextObject, FVector const& Start, FVector const& End, FVector const& HitLocation);
    static void DrawShootHitLocation(UObject* WorldContextObject, FVector const& HitLocation);
};
