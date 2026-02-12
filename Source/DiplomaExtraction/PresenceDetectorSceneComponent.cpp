// Fill out your copyright notice in the Description page of Project Settings.

#include "PresenceDetectorSceneComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"

void UPresenceDetectorSceneComponent::BeginPlay()
{
    Super::BeginPlay();

    SphereComponent = NewObject<USphereComponent>(this, TEXT("SphereComponent"));
    if (SphereComponent)
        return;

    SphereComponent->SetupAttachment(this);
    SphereComponent->bHiddenInSceneCapture = true;
    SphereComponent->bUseAttachParentBound = true;

    SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &UPresenceDetectorSceneComponent::OnBeginOverlap);
    SphereComponent->OnComponentEndOverlap.AddDynamic(this, &UPresenceDetectorSceneComponent::OnEndOverlap);
}

void UPresenceDetectorSceneComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!IsValid(OtherActor))
        return;

    auto World = GetWorld();
    if (!World)
        return;

    if (TypeTracking == ETypeTracking::Player)
    {
        if (OtherActor->GetInstigatorController() == World->GetFirstPlayerController())
            ActorsInside.Add(OtherActor);

        CheckActorsInside();
        return;
    }
}

void UPresenceDetectorSceneComponent::OnEndOverlap(
    UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (!IsValid(OtherActor))
        return;

    auto World = GetWorld();
    if (!World)
        return;

    if (TypeTracking == ETypeTracking::Player)
    {
        if (OtherActor->GetInstigatorController() == World->GetFirstPlayerController())
            ActorsInside.Remove(OtherActor);

        CheckActorsInside();
        return;
    }
}

void UPresenceDetectorSceneComponent::CheckActorsInside()
{
    if (IsInside() == bIsInside)
        return;

    bIsInside = !bIsInside;

    if (bIsInside)
        OnZoneBecameOccupied.Broadcast();
    else
        OnZoneBecameEmpty.Broadcast();
}
