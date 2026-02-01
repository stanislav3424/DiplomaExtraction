// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "LogicInterface.h"
#include "AutoWidgetComponent.generated.h"

UCLASS(Blueprintable, ClassGroup = "UserInterface",
    hidecategories = (Object, Activation, "Components|Activation", Sockets, Base, Lighting, LOD, Mesh), editinlinenew,
    meta           = (BlueprintSpawnableComponent))
class DIPLOMAEXTRACTION_API UAutoWidgetComponent : public UWidgetComponent, public ILogicInterface
{
    GENERATED_BODY()

public:
    virtual ULogicBase* GetLogic_Implementation() override;
    virtual void        SetLogic_Implementation(ULogicBase* NewLogic) override;

private:
    UPROPERTY(Transient)
    ULogicBase* LogicBase;
};
