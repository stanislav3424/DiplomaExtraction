// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UW_Base.h"
#include "UW_InventoryGrid.generated.h"

UCLASS(Abstract, Blueprintable)
class DIPLOMAEXTRACTION_API UUW_InventoryGrid : public UUW_Base
{
    GENERATED_BODY()

protected:
    virtual void  LogicChanged(ULogicBase* OldLogic, ULogicBase* NewLogic);
    virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
        const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
        const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

    FIntVector2  GridSize      = FIntVector2::ZeroValue;
    FLinearColor GridColor     = FLinearColor(0.5f, 0.5f, 0.5f, 1.f);
};
