// Fill out your copyright notice in the Description page of Project Settings.

#include "UserWidgetLibrary.h"

FVector2D UUserWidgetLibrary::GetSizeInViewport(FIntVector2 const& Size)
{
    auto CellSize = GetCellSize();
    return FVector2D(Size.X * CellSize, Size.Y * CellSize);
}

FVector2D UUserWidgetLibrary::GetPositionInViewport(FIntVector2 const& Position)
{
    auto CellSize = GetCellSize();
    return FVector2D(Position.X * CellSize, Position.Y * CellSize);
}
