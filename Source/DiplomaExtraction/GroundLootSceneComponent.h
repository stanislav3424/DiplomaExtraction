// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SceneComponentBase.h"
#include "GroundLootSceneComponent.generated.h"

class USphereComponent;
class UGroundLootInventoryLogic;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DIPLOMAEXTRACTION_API UGroundLootSceneComponent : public USceneComponentBase
{
    GENERATED_BODY()

public:
    UGroundLootSceneComponent();

public:
    virtual void BeginPlay() override;
    virtual void OnRegister() override;

public:
    virtual void SetLogic_Implementation(ULogicBase* NewLogic) override;

protected:
    UFUNCTION()
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex);

private:
    UPROPERTY(EditAnywhere, Category = "Interaction")
    USphereComponent* SphereComponent;

    UPROPERTY(Transient)
    UGroundLootInventoryLogic* GroundLootInventoryLogic;
};
