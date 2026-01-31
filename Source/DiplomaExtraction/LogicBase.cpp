// Fill out your copyright notice in the Description page of Project Settings.

#include "LogicBase.h"
#include "SpawnLibrary.h"
#include "MacroLibrary.h"

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
	for (ULogicBase* Component : LogicComponents)
	{
		if (Component)
			Component->Deinitialize();
	}
	LogicComponents.Empty();
	OwnerLogic = nullptr;
}

void ULogicBase::AddLogicComponent(ULogicBase* Component)
{
	if (Component)
	{
		LogicComponents.Add(Component);
		Component->SetOwnerLogic(OwnerLogic);
	}
}

void ULogicBase::RemoveLogicComponent(ULogicBase* Component)
{
	if (Component)
	{
		LogicComponents.Remove(Component);
        Component->Deinitialize();
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

    RepresentationActor = World->SpawnActor<AActor>(AActor::StaticClass(), SpawnLocation, SpawnRotation);
    if (!IsValid(RepresentationActor))
        return nullptr;

    RepresentationActor->SetActorLocationAndRotation(SpawnLocation, SpawnRotation);

    return RepresentationActor;
}

void ULogicBase::Tick(float DeltaTime)
{
}
