// Fill out your copyright notice in the Description page of Project Settings.

#include "UserWidgetLibrary.h"

FVector2D UUserWidgetLibrary::GetSizeInViewport(FIntVector2 const& Size)
{
    auto CellSize = GetCellSize();
    return FVector2D(Size.X * CellSize, Size.Y * CellSize);
}
