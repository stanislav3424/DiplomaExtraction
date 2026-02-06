// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InitRowHandle.generated.h"

UENUM(BlueprintType)
enum class ETypeInit : uint8
{
    Disabled               UMETA(DisplayName = "Disabled"),
    PlacedInWorld          UMETA(DisplayName = "PlacedInWorld"),
    Spawned                UMETA(DisplayName = "Spawned"),
    PlacedInWorldOrSpawned UMETA(DisplayName = "PlacedInWorldOrSpawned"),
};

UCLASS(NotBlueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DIPLOMAEXTRACTION_API UInitRowHandle : public UActorComponent
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
    void         Init();

    UPROPERTY(EditDefaultsOnly, Category = "InitRowHandle")
    FDataTableRowHandle InitRowHandle;

    UPROPERTY(EditDefaultsOnly, Category = "InitRowHandle")
    ETypeInit TypeInit = ETypeInit::PlacedInWorld;
};
