// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LogicInterface.h"
#include "AutoAddLogicActorComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DIPLOMAEXTRACTION_API UAutoAddLogicActorComponent : public UActorComponent, public ILogicInterface
{
    GENERATED_BODY()

public:
    virtual ULogicBase* GetLogic_Implementation() override;
    virtual void        SetLogic_Implementation(ULogicBase* NewLogic) override;

private:
    UPROPERTY(Transient)
    ULogicBase* LogicBase;

    UPROPERTY(EditAnywhere, Category = "DataTableRowHandle")
    FDataTableRowHandle DataTableRowHandle;
};
