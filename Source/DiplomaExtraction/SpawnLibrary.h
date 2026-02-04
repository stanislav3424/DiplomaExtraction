// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SpawnLibrary.generated.h"

class ULogicBase;

UCLASS()
class DIPLOMAEXTRACTION_API USpawnLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    static AActor* SpawnActorByRowHandler(UObject* WorldContextObject, FDataTableRowHandle const& RowHandle,
        FVector const& SpawnLocation, FRotator const& SpawnRotation);

    static ULogicBase* SpawnLogicByRowHandler(UObject* WorldContextObject, FDataTableRowHandle const& RowHandle, AActor* InitActor = nullptr);
};
