// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorLogic.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "LogicLibrary.h"
#include "MacroLibrary.h"
#include "Row.h"
#include "QuestConditionLogic.h"

UDoorLogic::UDoorLogic()
{
    bIsTickEnabled = true;
}

void UDoorLogic::InitializeRowHandler(FDataTableRowHandle const& InitRowHandle)
{
    Super::InitializeRowHandler(InitRowHandle);

    auto Row = InitRowHandle.GetRow<FDoorRow>(FILE_FUNC);
    if (!Row)
        return;
}

void UDoorLogic::RepresentationActorChanged(AActor* NewRepresentationActor)
{
    if (!IsValid(NewRepresentationActor))
        return;

    if (CollisionBox)
    {
        CollisionBox->OnComponentBeginOverlap.RemoveDynamic(this, &UDoorLogic::OnBoxBeginOverlap);
        CollisionBox->OnComponentEndOverlap.RemoveDynamic(this, &UDoorLogic::OnBoxEndOverlap);
    }

    CollisionBox = nullptr;
    DoorMesh     = nullptr;

    CollisionBox = NewRepresentationActor->FindComponentByTag<UBoxComponent>(CollisionBoxTag);
    DoorMesh     = NewRepresentationActor->FindComponentByTag<UStaticMeshComponent>(DoorMeshTag);

    CHECK_FIELD_RETURN(CollisionBox)
    CHECK_FIELD_RETURN(DoorMesh)

    CurrentPosition = DoorMesh->GetRelativeLocation();
    TargetPosition  = CurrentPosition;

    CollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &UDoorLogic::OnBoxBeginOverlap);
    CollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &UDoorLogic::OnBoxEndOverlap);

    ChechQuestsCompleted();
}

void UDoorLogic::AttachedComponent(ULogicBase* NewComponent)
{
    Super::AttachedComponent(NewComponent);

    auto LocalQuestConditionLogic = Cast<UQuestConditionLogic>(NewComponent);
    if (!LocalQuestConditionLogic)
        return;

    QuestConditionLogic = LocalQuestConditionLogic;
}

void UDoorLogic::TickLogic(float DeltaTime)
{
    Super::TickLogic(DeltaTime);

    if (!DoorMesh)
        return;

    if (TargetPosition.Equals(CurrentPosition, KINDA_SMALL_NUMBER))
        return;

    FVector NewPosition = FMath::VInterpConstantTo(CurrentPosition, TargetPosition, DeltaTime, Speed);

    CurrentPosition = NewPosition;
    DoorMesh->SetRelativeLocation(CurrentPosition);
}

void UDoorLogic::SwitchDoor(bool bNewIsOpen)
{
    if (IsBlockedDoor())
        return;

    if (bIsOpen == bNewIsOpen)
        return;

    bIsOpen = bNewIsOpen;

    const float Sign = bIsOpen ? -1.f : 1.f;
    TargetPosition += FVector(0.f, Sign * DeltaLocation, 0.f);
}

bool UDoorLogic::ChechQuestsCompleted()
{
    bIsBlockedDoor = false;
    if (QuestConditionLogic)
        if (!QuestConditionLogic->IsAreAllQuestsCompleted())
            bIsBlockedDoor = true;

    DoorMesh->SetCanEverAffectNavigation(bIsBlockedDoor);
}

void UDoorLogic::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    auto Logic = ULogicLibrary::GetLogic(OtherActor);
    if (!Logic)
        return;

    OtherActors.Add(OtherActor);

    SwitchDoor(!OtherActors.IsEmpty());
}

void UDoorLogic::OnBoxEndOverlap(
    UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    auto Logic = ULogicLibrary::GetLogic(OtherActor);
    if (!Logic)
        return;

    OtherActors.Remove(OtherActor);

    SwitchDoor(!OtherActors.IsEmpty());
}
