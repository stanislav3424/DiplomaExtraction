// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "LogicInterface.h"
#include "GroundLootSceneComponent.generated.h"

class USphereComponent;
class UGroundLootInventoryLogic;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DIPLOMAEXTRACTION_API UGroundLootSceneComponent : public USceneComponent, public ILogicInterface
{
	GENERATED_BODY()

    UGroundLootSceneComponent();
public:
    virtual void BeginPlay() override;

public:
    virtual ULogicBase* GetLogic_Implementation() override;
    virtual void        SetLogic_Implementation(ULogicBase* NewLogic) override;

protected:
    UFUNCTION()
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
        const FHitResult& SweepResult);

    UFUNCTION()
    void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex);

private:
    UPROPERTY(Transient)
    ULogicBase* LogicBase;

    UPROPERTY(EditDefaultsOnly, Category = "Interaction")
    USphereComponent* SphereComponent;

    UPROPERTY(Transient)
    UGroundLootInventoryLogic* GroundLootInventoryLogic;
};
