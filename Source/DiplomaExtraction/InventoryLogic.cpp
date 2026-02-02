// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryLogic.h"
#include "SpawnLibrary.h"
#include "Row.h"
#include "MacroLibrary.h"
#include "ItemLogic.h"

void UInventoryLogic::InitializeRowHandler(FDataTableRowHandle const& InitRowHandle)
{
    Super::InitializeRowHandler(InitRowHandle);
    
    auto Row = InitRowHandle.GetRow<FInventoryLogicRow>(FILE_FUNC);

    if (!Row)
        return;

    CheckValidInventorySize();

    InitializeInventory();
}

void UInventoryLogic::CheckValidInventorySize()
{
    if (IsValidInventorySize(this))
        return;
    InventorySize = FIntVector2(1, 1);
    UE_LOG(InitGameLogic, Warning, FILE_FUNC TEXT("Invalid inventory size detected. Resetting to default (1, 1)."))
}

void UInventoryLogic::InitializeInventory()
{
    InventoryGrid.SetNum(InventorySize.X * InventorySize.Y);
}

bool UInventoryLogic::IsValidInventorySize(ULogicBase* Item)
{
    auto InventoryLogic = Cast<UInventoryLogic>(Item);
    return InventoryLogic && InventoryLogic->InventorySize.X > 0 && InventoryLogic->InventorySize.Y > 0;
}

int32 UInventoryLogic::PositionToIndex(FIntVector2 const& Position) const
{
    return Position.Y * InventorySize.X + Position.X;
}

FIntVector2 UInventoryLogic::IndexToPosition(int32 Index)
{
    return FIntVector2(Index % InventorySize.X, Index / InventorySize.X);
}

bool UInventoryLogic::IsPositionOccupied(FIntVector2 const& Position) const
{
    int32 Index = PositionToIndex(Position);
    if (InventoryGrid.IsValidIndex(Index))
        if (auto Item = InventoryGrid[Index])
            return true;
    return false;
}

bool UInventoryLogic::IsPositionValid(FIntVector2 const& Position) const
{
    int32 Index = PositionToIndex(Position);
    if (InventoryGrid.IsValidIndex(Index))
        return true;
    return false;
}

bool UInventoryLogic::CanAddItemToPosition(ULogicBase* Item, FIntVector2 const& Position, bool Rotation)
{
    if (!IsPositionValid(Position))
        return false;

    auto ItemLogic = Cast<UItemLogic>(Item);
    if (ItemLogic)
        return false;

    auto ItemSize = UItemLogic::GetRotationSize(ItemLogic->GetItemSize(), Rotation);

    return true;
}
