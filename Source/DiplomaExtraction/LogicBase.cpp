// Fill out your copyright notice in the Description page of Project Settings.

#include "LogicBase.h"
#include "SpawnLibrary.h"
#include "LogicLibrary.h"
#include "MacroLibrary.h"
#include "LogicInterface.h"
#include "Row.h"

void ULogicBase::InitializeRowHandler_Internal(FDataTableRowHandle const& InitRowHandle)
{
    RowHandle = InitRowHandle;
    auto Row  = RowHandle.GetRow<FLogicBaseRow>(FILE_FUNC);
    if (!Row)
        return;
    RepresentationActorClass = Row->RepresentationActorClass;
    for (auto const& ComponentRowHandle : Row->ComponentRows)
    {
        auto ComponentLogic = USpawnLibrary::SpawnLogicByRowHandler(this, ComponentRowHandle, nullptr);
        if (ComponentLogic)
            AddLogicComponent(ComponentLogic);
    }
    InitializeRowHandler(InitRowHandle);
}

void ULogicBase::InitializeRowHandler(FDataTableRowHandle const& InitRowHandle)
{
    
}

void ULogicBase::SetOwnerLogic(ULogicBase* NewOwnerLogic)
{
    auto OldOwnerLogic = OwnerLogic;
    OwnerLogic         = NewOwnerLogic;

    if (OldOwnerLogic)
        OldOwnerLogic->RemoveChildLogic_Internal(this);

    DestroyRepresentationActor();

    OwnerLogicChange(NewOwnerLogic);
}

void ULogicBase::OwnerLogicChange(ULogicBase* NewOwnerLogic)
{
}

void ULogicBase::RemoveChildLogic_Internal(ULogicBase* ChildLogic)
{
    if (ChildLogic)
        LogicComponents.Remove(ChildLogic);
    RemoveChildLogic(ChildLogic);
}

void ULogicBase::RemoveChildLogic(ULogicBase* ChildLogic)
{
    
}

//void ULogicBase::DestroyLogic()
//{
//	for (auto Component : LogicComponents)
//		if (Component)
//			Component->DestroyLogic();
//	LogicComponents.Empty();
//	OwnerLogic = nullptr;
//    DestroyRepresentationActor();
//}

void ULogicBase::AddLogicComponent(ULogicBase* Component)
{
	if (Component)
	{
		LogicComponents.AddUnique(Component);
        Component->SetOwnerLogic(this);
	}
}

void ULogicBase::RemoveLogicComponent(ULogicBase* Component)
{
	if (Component)
	{
		LogicComponents.Remove(Component);
        Component->SetOwnerLogic(nullptr);
    }
}

AActor* ULogicBase::SpawnRepresentationActor(FVector const& SpawnLocation, FRotator const& SpawnRotation)
{
    if (IsValid(RepresentationActor))
    {
        RepresentationActor->SetActorLocationAndRotation(SpawnLocation, SpawnRotation);
        return RepresentationActor;
    }

    CHECK_FIELD_RETURN_VALUE(RepresentationActorClass, nullptr);

    auto World = GetWorld();
    if (!World)
        return nullptr;

    auto LocalRepresentationActor = World->SpawnActor<AActor>(RepresentationActorClass, SpawnLocation, SpawnRotation);
    if (!IsValid(LocalRepresentationActor))
        return nullptr;

    HardSetRepresentationActor(LocalRepresentationActor);

    return LocalRepresentationActor;
}

void ULogicBase::HardSetRepresentationActor(AActor* NewRepresentationActor)
{
    if (!IsValid(NewRepresentationActor))
        return;

    if (IsValid(RepresentationActor))
    {
        RepresentationActor->Destroy();
        RepresentationActor = nullptr;
    }

    RepresentationActor = NewRepresentationActor;

    ULogicLibrary::SetLogic(NewRepresentationActor, this);

    for (auto Component : NewRepresentationActor->GetComponents())
        ULogicLibrary::SetLogic(Component, this);

}

void ULogicBase::DestroyRepresentationActor()
{
    if (IsValid(RepresentationActor))
    {
        RepresentationActor->Destroy();
        RepresentationActor = nullptr;
    }
}

AActor* ULogicBase::DropToGround(FVector const& SpawnLocation, FRotator const& SpawnRotation)
{
    SetOwnerLogic(nullptr);

    auto Actor = SpawnRepresentationActor(SpawnLocation - FVector(0.f, 0.f, -2000.f), SpawnRotation);
    if (!IsValid(Actor))
        return nullptr;

    // 

    Actor->SetActorLocation(SpawnLocation);

    SetSimulatePhysics();

    return Actor;
}

void ULogicBase::SetSimulatePhysics()
{
    if (!IsValid(RepresentationActor))
        return;
    auto PrimitiveComponent = Cast<UPrimitiveComponent>(RepresentationActor->GetRootComponent());
    if (!PrimitiveComponent)
        return;
    PrimitiveComponent->SetSimulatePhysics(true);
    PrimitiveComponent->SetEnableGravity(true);
    PrimitiveComponent->WakeAllRigidBodies();
}

void ULogicBase::TickLogic(float DeltaTime)
{
}

void ULogicBase::Tick(float DeltaTime)
{
    auto World = GetWorld();
    if (World && !World->IsPaused())
        TickLogic(DeltaTime);
}