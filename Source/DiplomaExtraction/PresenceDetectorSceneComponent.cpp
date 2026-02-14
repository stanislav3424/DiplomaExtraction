// Fill out your copyright notice in the Description page of Project Settings.

#include "PresenceDetectorSceneComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "MacroLibrary.h"

UPresenceDetectorSceneComponent::UPresenceDetectorSceneComponent()
{
    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
    SphereComponent->SetupAttachment(this);
}

void UPresenceDetectorSceneComponent::BeginPlay()
{
    Super::BeginPlay();

     if (!SphereComponent)
        return;

    SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &UPresenceDetectorSceneComponent::OnBeginOverlap);
    SphereComponent->OnComponentEndOverlap.AddDynamic(this, &UPresenceDetectorSceneComponent::OnEndOverlap);
}

void UPresenceDetectorSceneComponent::OnRegister()
{
    Super::OnRegister();

    if (SphereComponent)
    {
        SphereComponent->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
    }
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
