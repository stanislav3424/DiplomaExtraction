// Fill out your copyright notice in the Description page of Project Settings.

#include "PresenceDetectorSceneComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "MacroLibrary.h"
#include "EnumLibrary.h"

UPresenceDetectorSceneComponent::UPresenceDetectorSceneComponent()
{
    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
    SphereComponent->SetupAttachment(this);
}

void UPresenceDetectorSceneComponent::BeginPlay()
{
    Super::BeginPlay();

    ComponentTags.AddUnique(UEnumLibrary::EnumToName(TypeTracking));

     if (!SphereComponent)
        return;

    SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &UPresenceDetectorSceneComponent::OnBeginOverlap);
    SphereComponent->OnComponentEndOverlap.AddDynamic(this, &UPresenceDetectorSceneComponent::OnEndOverlap);
}

void UPresenceDetectorSceneComponent::OnRegister()
{
    Super::OnRegister();

    if (SphereComponent)
        SphereComponent->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void UPresenceDetectorSceneComponent::SetTypeTracking(ETypeTracking const& NewTypeTracking)
{
    if (TypeTracking == NewTypeTracking)
        return;

    ComponentTags.Remove(UEnumLibrary::EnumToName(TypeTracking));
    TypeTracking = NewTypeTracking;
    ComponentTags.AddUnique(UEnumLibrary::EnumToName(TypeTracking));

    ActorsInside.Empty();

    if (SphereComponent)
        SphereComponent->UpdateOverlaps();
}

void UPresenceDetectorSceneComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (TypeTracking == ETypeTracking::None)
        return;

    if (!IsValid(OtherActor))
        return;

    auto World = GetWorld();
    if (!World)
        return;

    if (TypeTracking == ETypeTracking::Player)
    {
        if (OtherActor->GetInstigatorController() == World->GetFirstPlayerController())
        {
            if (!ActorsInside.Contains(OtherActor))
                OnNewActor.Broadcast(OtherActor);

            ActorsInside.Add(OtherActor);

            CheckActorsInside();
        }
    }
}

void UPresenceDetectorSceneComponent::OnEndOverlap(
    UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (TypeTracking == ETypeTracking::None)
        return;

    if (!IsValid(OtherActor))
        return;

    auto World = GetWorld();
    if (!World)
        return;

    if (TypeTracking == ETypeTracking::Player)
    {
        if (OtherActor->GetInstigatorController() == World->GetFirstPlayerController())
        {
            ActorsInside.Remove(OtherActor);

            CheckActorsInside();
        }
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
