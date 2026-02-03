// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UW_Base.h"
#include "UW_Icon.generated.h"

class UImage;

UCLASS(Abstract, Blueprintable)
class DIPLOMAEXTRACTION_API UUW_Icon : public UUW_Base
{
	GENERATED_BODY()
	
	protected:
    virtual void LogicChanged(ULogicBase* OldLogic, ULogicBase* NewLogic) override;
    virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
    void         WidgetSizeChanged(const FVector2D& NewSize);

    UPROPERTY(meta = (BindWidget))
    UImage* IconImage;

    FVector2D LastWidgetSize = FVector2D::ZeroVector;

    UPROPERTY(Transient)
    UMaterialInstanceDynamic* IconMID;
};
