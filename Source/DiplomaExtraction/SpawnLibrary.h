// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SpawnLibrary.generated.h"

class ULogicBase;

USTRUCT(BlueprintType)
struct FLogicBaseRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<ULogicBase> LogicClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AActor> RepresentationActorClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FDataTableRowHandle> ComponentRows;
};

USTRUCT(BlueprintType)
struct FStaminaLogicRow : public FLogicBaseRow
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxStamina = 100.0f;
};

USTRUCT(BlueprintType)
struct FHealthLogicRow : public FLogicBaseRow
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MaxHealth = 100.0f;
};

USTRUCT(BlueprintType)
struct FInventoryLogicRow : public FLogicBaseRow
{
    GENERATED_BODY()

    // Reserved for future inventory settings
};

UENUM(BlueprintType)
enum class EEquipmentSlot : uint8
{
    None,
    Hands,
    Head,
    Chest,
    BackPack,
    BackWeapon,
};

USTRUCT(BlueprintType)
struct FItemLogicRow : public FLogicBaseRow
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EEquipmentSlot EquipmentSlot = EEquipmentSlot::None;
};

UCLASS()
class DIPLOMAEXTRACTION_API USpawnLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    static AActor* SpawnActorByRowHandler(UObject* WorldContextObject, FDataTableRowHandle const& RowHandle,
        FVector const& SpawnLocation, FRotator const& SpawnRotation);

    static ULogicBase* SpawnLogicByRowHandler(UObject* WorldContextObject, FDataTableRowHandle const& RowHandle);
};
