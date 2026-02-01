// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "LogicBase.generated.h"

UCLASS(Abstract, NotBlueprintable)
class DIPLOMAEXTRACTION_API ULogicBase : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

    // Initialize
public:
    virtual void InitializeRowHandler(FDataTableRowHandle const& InitRowHandle);

    FDataTableRowHandle const& GetDataTableRowHandle() const { return RowHandle; }

private:
    FDataTableRowHandle RowHandle;

    // Components
protected:
    virtual void SetOwnerLogic(ULogicBase* IntOwnerLogic);
    virtual void Deinitialize();

public:
    ULogicBase* GetOwnerLogic() const { return OwnerLogic; }

    void AddLogicComponent(ULogicBase* Component);
    void RemoveLogicComponent(ULogicBase* Component);
    template <typename TypeComponent = ULogicBase> TypeComponent* GetLogicComponent()
    {
        const UClass* Wanted = TypeComponent::StaticClass();
        for (auto* Component : LogicComponents)
            if (Component && Component->IsA(Wanted))
                return Cast<TypeComponent>(Component);
        return nullptr;
    }
    void GetLogicComponents(TArray<ULogicBase*>& OutComponents) const { OutComponents = LogicComponents; }

private:
    UPROPERTY()
    ULogicBase* OwnerLogic;

    UPROPERTY()
    TArray<ULogicBase*> LogicComponents;

    // RepresentationActor
public:
    AActor* GetRepresentationActor() const { return RepresentationActor; }
    AActor* SpawnRepresentationActor(FVector const& SpawnLocation, FRotator const& SpawnRotation);
    void    HardSetRepresentationActor(AActor* NewRepresentationActor);

private:
    UPROPERTY(Transient)
    AActor* RepresentationActor;

    UPROPERTY(Transient)
    TSubclassOf<AActor> RepresentationActorClass;

    // Tickable
public:
    virtual void    Tick(float DeltaTime) override;
    virtual bool    IsTickable() const override { return bIsTickEnabled; }
    virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(ULogicBase, STATGROUP_Tickables); }

    bool bIsTickEnabled = false;
};
