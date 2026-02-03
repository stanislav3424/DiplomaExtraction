// Fill out your copyright notice in the Description page of Project Settings.

#include "UW_Frame.h"

int32 UUW_Frame::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect,
    FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle,
    bool bParentEnabled) const
{
    int32 Layer = Super::NativePaint(
        Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

    const FVector2D Size = AllottedGeometry.GetLocalSize();
    TArray<FVector2D> Points;

    FVector2D TopLeft     = FVector2D(0.f, 0.f);
    FVector2D TopRight    = FVector2D(0.f, Size.Y);
    FVector2D BottomLeft  = FVector2D(Size.X, 0.f);
    FVector2D BottomRight = FVector2D(Size.X, Size.Y);

    Points.Add(TopLeft);
    Points.Add(TopRight);
    Points.Add(BottomRight);
    Points.Add(BottomLeft);
    Points.Add(TopLeft);
    FSlateDrawElement::MakeLines(OutDrawElements, Layer + 1, AllottedGeometry.ToPaintGeometry(), Points,
        ESlateDrawEffect::None, BorderColor);

    return Layer + 1;
}