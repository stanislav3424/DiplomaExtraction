// Fill out your copyright notice in the Description page of Project Settings.

#include "GroundLootSceneComponent.h"
#include "Components/SphereComponent.h"
#include "GroundLootInventoryLogic.h"
#include "CharacterLogic.h"
#include "LogicBase.h"
#include "ItemLogic.h"
#include "LogicLibrary.h"
#include "Row.h"

void UGroundLootSceneComponent::BeginPlay()
{
    Super::BeginPlay();

    if (!SphereComponent)
        return;

    SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &UGroundLootSceneComponent::OnBeginOverlap);
    SphereComponent->OnComponentEndOverlap.AddUniqueDynamic(this, &UGroundLootSceneComponent::OnEndOverlap);
}

void UGroundLootSceneComponent::OnRegister()
{
    Super::OnRegister();

    /*auto Owner = GetOwner();
    if (!Owner)
        return;

    if (!SphereComponent)
    {
        SphereComponent = NewObject<USphereComponent>(Owner, TEXT("SphereComponent"));
        if (SphereComponent)
        {
            SphereComponent->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
            SphereComponent->RegisterComponent();
            SphereComponent->SetMobility(EComponentMobility::Movable);
            SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
            SphereComponent->bHiddenInSceneCapture = true;
        }
    }*/
}

void UGroundLootSceneComponent::OnUnregister()
{

    /*if (SphereComponent)
    {
        SphereComponent->DestroyComponent();
        SphereComponent = nullptr;
    }*/

    Super::OnUnregister();
}

void UGroundLootSceneComponent::TickComponent(
    float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

ULogicBase* UGroundLootSceneComponent::GetLogic_Implementation()
{
    return LogicBase;
}

void UGroundLootSceneComponent::SetLogic_Implementation(ULogicBase* NewLogic)
{
    LogicBase = NewLogic;

    auto CharacterLogic = Cast<UCharacterLogic>(LogicBase);
    if (!CharacterLogic)
        return;

    GroundLootInventoryLogic = NewObject<UGroundLootInventoryLogic>(GetWorld(), UGroundLootInventoryLogic::StaticClass());
    if (!GroundLootInventoryLogic)
        return;

    GroundLootInventoryLogic->InitSize();

    CharacterLogic->AddLogicComponent(GroundLootInventoryLogic);
}

void UGroundLootSceneComponent::OnBeginOverlap(
    UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (!GroundLootInventoryLogic)
        return;

    auto Logic = ULogicLibrary::GetLogic(OtherActor);
    if (!Logic)
        return;

    auto ItemComponent = Logic->GetLogicComponent<UItemLogic>();
    if (!ItemComponent)
        return;

    GroundLootInventoryLogic->AddItemToFirstAvailablePosition(Logic);
}

void UGroundLootSceneComponent::OnEndOverlap(
    UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (!GroundLootInventoryLogic)
        return;

    auto Logic = ULogicLibrary::GetLogic(OtherActor);
    if (!Logic)
        return;

    auto ItemComponent = Logic->GetLogicComponent<UItemLogic>();
    if (!ItemComponent)
        return;

    GroundLootInventoryLogic->RemoveItemFromInventory(Logic);
}

