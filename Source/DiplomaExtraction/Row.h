// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Row.generated.h"

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

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FIntVector2 InventorySize = FIntVector2(1, 1);
};

USTRUCT(BlueprintType)
struct FCharacterLogicRow : public FLogicBaseRow
{
    GENERATED_BODY()
};

UENUM(BlueprintType)
enum class EEquipmentSlot : uint8
{
    None UMETA(DisplayName = "None"), 
    Hands UMETA(DisplayName = "Hands"),
    //Head,
    //Chest,
    Backpack UMETA(DisplayName = "Backpack"),
    //BackWeapon,
};

USTRUCT(BlueprintType)
struct FEquipmentLogicRow : public FLogicBaseRow
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EEquipmentSlot EquipmentSlot = EEquipmentSlot::None;
};

USTRUCT(BlueprintType)
struct FItemLogicRow : public FLogicBaseRow
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FIntVector2 ItemSize = FIntVector2(1, 1);
};

USTRUCT(BlueprintType)
struct FWeaponLogicRow : public FLogicBaseRow
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Damage = 35.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float RateOfFire = 600.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Ammo = 30.f;
};

USTRUCT(BlueprintType)
struct FTemplateCharacterRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FDataTableRowHandle CharacterRow;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<EEquipmentSlot, FDataTableRowHandle> Equipment;
};

UENUM(BlueprintType)
enum class ETypeQuest : uint8
{
    None  UMETA(DisplayName = "None"),
    GreenCard UMETA(DisplayName = "GreenCard"),
    BlueCard  UMETA(DisplayName = "BlueCard"),
    RedCard UMETA(DisplayName = "RedCard"),
    PowerBoard UMETA(DisplayName = "PowerBoard"),
};

USTRUCT(BlueprintType)
struct FQuestRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ETypeQuest TypeQuest = ETypeQuest::None;
};
