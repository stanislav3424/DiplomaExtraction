// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemLogic.h"
#include "Row.h"
#include "MacroLibrary.h"

void UItemLogic::InitializeRowHandler(FDataTableRowHandle const& InitRowHandle)
{
    Super::InitializeRowHandler(InitRowHandle);

    auto ItemRow = InitRowHandle.GetRow<FItemLogicRow>(FILE_FUNC);
    if (!ItemRow)
        return;

    ItemSize = ItemRow->ItemSize;

    CheckValidItemSize();
}

FIntVector2 UItemLogic::GetRotationSize(FIntVector2 const& OriginalSize, bool Rotation)
{
    if (Rotation)
        return FIntVector2(OriginalSize.Y, OriginalSize.X);
    return OriginalSize;
}

bool UItemLogic::IsValidItemSize(ULogicBase* Item)
{
    auto ItemLogic = Cast<UItemLogic>(Item);
    return ItemLogic && ItemLogic->ItemSize.X > 0 && ItemLogic->ItemSize.Y > 0;
}

void UItemLogic::CheckValidItemSize()
{
    if (IsValidItemSize(this))
        return;
    ItemSize = FIntVector2(1, 1);
    UE_LOG(InitGameLogic, Warning, FILE_FUNC TEXT("Invalid item size detected. Resetting to default (1, 1)."))
}
