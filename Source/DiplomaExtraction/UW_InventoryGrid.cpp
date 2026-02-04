// Fill out your copyright notice in the Description page of Project Settings.

#include "UW_InventoryGrid.h"
#include "InventoryLogic.h"

void UUW_InventoryGrid::LogicChanged(ULogicBase* OldLogic, ULogicBase* NewLogic)
{
    Super::LogicChanged(OldLogic, NewLogic);

    auto InventoryLogic = Cast<UInventoryLogic>(NewLogic);

    if (!InventoryLogic)
        return;

    GridSize = InventoryLogic->GetInventorySize();
}

int32 UUW_InventoryGrid::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
    const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
    const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
    int32 RetLayer = Super::NativePaint(
        Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

    const FVector2D LocalSize  = AllottedGeometry.GetLocalSize();
    const float     CellWidth  = LocalSize.X / static_cast<float>(GridSize.X);
    const float     CellHeight = LocalSize.Y / static_cast<float>(GridSize.Y);

    const float LayoutScale    = AllottedGeometry.GetAccumulatedLayoutTransform().GetScale();
    const float PixelThickness = 1.0f / FMath::Max(LayoutScale, 1e-6f);
    const float HalfThickness  = PixelThickness * 0.5f;

    auto* WhiteBrush = FCoreStyle::Get().GetBrush("WhiteBrush");
    int32 GridLayer  = RetLayer + 1;

    for (int32 Col = 1; Col < GridSize.X; ++Col)
    {
        const float     XPosPhys  = FMath::RoundToFloat(Col * CellWidth * LayoutScale);
        const float     XPosLocal = XPosPhys / LayoutScale;
        const FVector2D Position(XPosLocal - HalfThickness, 0.0f);
        const float     HeightLocal = LocalSize.Y / LayoutScale;
        const FVector2D BoxSize(PixelThickness, HeightLocal);

        const FPaintGeometry PaintGeom =
            AllottedGeometry.ToPaintGeometry(BoxSize, FSlateLayoutTransform(LayoutScale, Position));
        FSlateDrawElement::MakeBox(
            OutDrawElements, GridLayer, PaintGeom, WhiteBrush, ESlateDrawEffect::None, GridColor);
    }

    for (int32 Row = 1; Row < GridSize.Y; ++Row)
    {
        const float     YPosPhys  = FMath::RoundToFloat(Row * CellHeight * LayoutScale);
        const float     YPosLocal = YPosPhys / LayoutScale;
        const FVector2D Position(0.0f, YPosLocal - HalfThickness);
        const float     WidthLocal = LocalSize.X / LayoutScale;
        const FVector2D BoxSize(WidthLocal, PixelThickness);

        const FPaintGeometry PaintGeom =
            AllottedGeometry.ToPaintGeometry(BoxSize, FSlateLayoutTransform(LayoutScale, Position));
        FSlateDrawElement::MakeBox(
            OutDrawElements, GridLayer, PaintGeom, WhiteBrush, ESlateDrawEffect::None, GridColor);
    }

    return GridLayer;
}
