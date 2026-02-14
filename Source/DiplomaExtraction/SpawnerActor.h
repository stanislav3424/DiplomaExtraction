// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnerActor.generated.h"

USTRUCT(BlueprintType) struct FUnitSpawnEntry
{
    GENERATED_BODY() 
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite) 
    FDataTableRowHandle DataTableRowHandle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite) 
    int32 Count = 0;
};

class ULogicBase;
class UPresenceDetectorSceneComponent;

UCLASS(Blueprintable, Abstract)
class DIPLOMAEXTRACTION_API ASpawnerActor : public AActor
{
    GENERATED_BODY()

public:
    ASpawnerActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

private:
    void FillQueue();
    void SpawnUnit();

    UPROPERTY(EditAnywhere, Category = "DifficultyUnitSets") 
    TArray<FUnitSpawnEntry> Units;

    UPROPERTY(EditAnywhere)
    UPresenceDetectorSceneComponent* PresenceDetector;

    TQueue<FDataTableRowHandle> Queue;

    UFUNCTION()
    void OnDeathUnit(ULogicBase* LogicBase, AActor* Actor);
};
