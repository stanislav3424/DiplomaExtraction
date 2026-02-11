// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LogicBase.h"
#include "DoorLogic.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UQuestConditionLogic;

UCLASS(NotBlueprintable)
class DIPLOMAEXTRACTION_API UDoorLogic : public ULogicBase
{
    GENERATED_BODY()

    UDoorLogic();

protected:
    virtual void InitializeRowHandler(FDataTableRowHandle const& InitRowHandle) override;
    virtual void RepresentationActorChanged(AActor* NewRepresentationActor) override;
    virtual void AttachedComponent(ULogicBase* NewComponent) override;

public:
    virtual void TickLogic(float DeltaTime);
    void         SwitchDoor(bool bNewIsOpen);
    bool         IsBlockedDoor() const { return bIsBlockedDoor; };

    bool ChechQuestsCompleted();

private:
    UPROPERTY(Transient)
    UBoxComponent* CollisionBox;

    UPROPERTY(Transient)
    UStaticMeshComponent* DoorMesh;

    FName CollisionBoxTag = TEXT("CollisionBox");
    FName DoorMeshTag     = TEXT("DoorMesh");

    UPROPERTY(Transient)
    TSet<AActor*> OtherActors;

    bool bIsOpen = false;
    bool bIsBlockedDoor = false;

    FVector CurrentPosition = FVector::ZeroVector;
    FVector TargetPosition  = FVector::ZeroVector;

    float Speed = 150.f;
    float DeltaLocation = 150;

    UPROPERTY(Transient)
    UQuestConditionLogic* QuestConditionLogic;

    UFUNCTION()
    void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnBoxEndOverlap(
        UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
