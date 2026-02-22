// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PresenceDetectorSceneComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnZoneBecameOccupied);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnZoneBecameEmpty);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewActor, AActor*, NewActor);

class USphereComponent;

UENUM(BlueprintType)
enum class ETypeTracking : uint8
{
    None   UMETA(DisplayName = "None"),
    Player UMETA(DisplayName = "Player"),
    Any    UMETA(DisplayName = "Any"),
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DIPLOMAEXTRACTION_API UPresenceDetectorSceneComponent : public USceneComponent
{
    GENERATED_BODY()

public:
    UPresenceDetectorSceneComponent();

protected:
    virtual void BeginPlay() override;
    virtual void OnRegister() override;

public:
    UFUNCTION(BlueprintCallable)
    bool IsInside() const { return !ActorsInside.IsEmpty(); };

    UPROPERTY(BlueprintAssignable)
    FOnZoneBecameOccupied OnZoneBecameOccupied;

    UPROPERTY(BlueprintAssignable)
    FOnZoneBecameEmpty OnZoneBecameEmpty;

    UPROPERTY(BlueprintAssignable)
    FOnNewActor OnNewActor;

    UFUNCTION(BlueprintCallable)
    TArray<AActor*> GetActorsInside() { return ActorsInside.Array(); };

    void SetTypeTracking(ETypeTracking const& NewTypeTracking);

private:
    UFUNCTION()
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex);

    void CheckActorsInside();

    UPROPERTY(Transient)
    TSet<AActor*> ActorsInside;

    UPROPERTY(EditAnywhere, Instanced, Category = "Interaction")
    USphereComponent* SphereComponent;

    UPROPERTY(EditAnywhere, Category = "Interaction")
    ETypeTracking TypeTracking = ETypeTracking::None;

    bool bIsInside = false;
};
