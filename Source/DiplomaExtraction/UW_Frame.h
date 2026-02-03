// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UW_Base.h"
#include "UW_Frame.generated.h"

UCLASS(NotBlueprintable)
class DIPLOMAEXTRACTION_API UUW_Frame : public UUW_Base
{
    GENERATED_BODY()

protected:
    virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
        const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
        const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

    FLinearColor BorderColor = FLinearColor::Black;
};