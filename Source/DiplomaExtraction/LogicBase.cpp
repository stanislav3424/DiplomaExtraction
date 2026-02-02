// Fill out your copyright notice in the Description page of Project Settings.

#include "LogicBase.h"
#include "SpawnLibrary.h"
#include "LogicLibrary.h"
#include "MacroLibrary.h"
#include "LogicInterface.h"

void ULogicBase::InitializeRowHandler(FDataTableRowHandle const& InitRowHandle)
{
    RowHandle = InitRowHandle;
    auto LogicRow = RowHandle.GetRow<FLogicBaseRow>(FILE_FUNC);
    if (!LogicRow)
		return;
	RepresentationActorClass = LogicRow->RepresentationActorClass;
	for (auto const& ComponentRowHandle : LogicRow->ComponentRows)
	{
		auto ComponentLogic = USpawnLibrary::SpawnLogicByRowHandler(this, ComponentRowHandle);
		if (ComponentLogic)
			AddLogicComponent(ComponentLogic);
    }
}

void ULogicBase::SetOwnerLogic(ULogicBase* IntOwnerLogic)
{
    OwnerLogic = IntOwnerLogic;
}

void ULogicBase::Deinitialize()
{
	for (auto Component : LogicComponents)
		if (Component)
			Component->Deinitialize();
	LogicComponents.Empty();
	OwnerLogic = nullptr;
}

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

    auto LocalRepresentationActor = World->SpawnActor<AActor>(AActor::StaticClass(), SpawnLocation, SpawnRotation);
    if (!IsValid(LocalRepresentationActor))
        return nullptr;

    HardSetRepresentationActor(LocalRepresentationActor);

    LocalRepresentationActor->SetActorLocationAndRotation(SpawnLocation, SpawnRotation);

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

void ULogicBase::TickLogic(float DeltaTime)
{
}

void ULogicBase::Tick(float DeltaTime)
{
    auto World = GetWorld();
    if (World && !World->IsPaused())
        TickLogic(DeltaTime);
}