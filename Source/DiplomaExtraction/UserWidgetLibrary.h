// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UserWidgetLibrary.generated.h"

UCLASS()
class DIPLOMAEXTRACTION_API UUserWidgetLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    static FVector2D GetSizeInViewport(FIntVector2 const& Size);
    static float     GetCellSize() { return 25.f; }
};
