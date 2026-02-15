// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "LogicBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRepresentationActorChanged, AActor*, NewRepresentationActor);

UCLASS(NotBlueprintable)
class DIPLOMAEXTRACTION_API ULogicBase : public UObject, public FTickableGameObject
{
	GENERATED_BODY()

    friend class USpawnLibrary;

    // Initialize
private:
    void InitializeRowHandler_Internal(FDataTableRowHandle const& InitRowHandle);

protected:
    virtual void InitializeRowHandler(FDataTableRowHandle const& InitRowHandle);

public:
    FDataTableRowHandle const& GetRowHandle() const { return RowHandle; }

private:
    FDataTableRowHandle RowHandle;

    // Components
private:
    virtual void SetOwnerLogic(ULogicBase* NewOwnerLogic);

protected:
    virtual void OwnerLogicChange(ULogicBase* OldOwnerLogic, ULogicBase* NewOwnerLogic);

private:
    void RemoveChildLogic_Internal(ULogicBase* ChildLogic);

protected:
    virtual void RemoveChildLogic(ULogicBase* ChildLogic);
    // virtual void DestroyLogic();

public:
    ULogicBase* GetOwnerLogic() const { return OwnerLogic; }

    void AddLogicComponent(ULogicBase* Component);
    void RemoveLogicComponent(ULogicBase* Component);

protected:
    virtual void AttachedComponent(ULogicBase* NewComponent);

public:
    template <typename TypeComponent = ULogicBase> TypeComponent* GetLogicComponent(bool bIncludeChildren = false)
    {
        auto Wanted = TypeComponent::StaticClass();
        for (auto Component : LogicComponents)
        {
            if (!Component)
                continue;
            if (Component->IsA(Wanted))
                return Cast<TypeComponent>(Component);
            if (bIncludeChildren)
                if (auto Found = Component->GetLogicComponent<TypeComponent>(bIncludeChildren))
                    return Found;
        }
        return nullptr;
    }

    template <typename TypeComponent = ULogicBase>
    void GetLogicComponents(TArray<TypeComponent*>& OutComponents, bool bIncludeChildren = false)
    {
        auto Wanted = TypeComponent::StaticClass();
        for (auto Component : LogicComponents)
        {
            if (!Component)
                continue;
            if (Component->IsA(Wanted))
                OutComponents.Add(Cast<TypeComponent>(Component));
            if (bIncludeChildren)
                Component->GetLogicComponents<TypeComponent>(OutComponents, bIncludeChildren);
        }
    }

private:
    UPROPERTY(Transient)
    ULogicBase* OwnerLogic;

    UPROPERTY(Transient)
    TArray<ULogicBase*> LogicComponents;

    // RepresentationActor
public:
    AActor*      GetRepresentationActor() const { return RepresentationActor; }
    AActor*      GetRepresentationActor() { return RepresentationActor; }
    AActor*      SpawnRepresentationActor(FVector const& SpawnLocation, FRotator const& SpawnRotation);
    void         HardSetRepresentationActor(AActor* NewRepresentationActor);
    void         DestroyRepresentationActor();
    AActor*      DropToGround(FVector const& SpawnLocation, FRotator const& SpawnRotation);
    virtual void SetSimulatePhysics();

    FOnRepresentationActorChanged OnRepresentationActorChanged;
    void BroadcastOnRepresentationActorChanged() { OnRepresentationActorChanged.Broadcast(GetRepresentationActor()); };

protected:
    virtual void RepresentationActorChanged(AActor* NewRepresentationActor) {};

private:
    UPROPERTY(Transient)
    AActor* RepresentationActor;

    UPROPERTY(Transient)
    TSubclassOf<AActor> RepresentationActorClass;

    // Tickable
public:
    virtual void TickLogic(float DeltaTime);

    bool bIsTickEnabled = false;

private:
    virtual void    Tick(float DeltaTime) override;
    virtual bool    IsTickable() const override { return bIsTickEnabled; }
    virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(ULogicBase, STATGROUP_Tickables); }
    virtual bool    IsTickableWhenPaused() const override { return false; }
};
