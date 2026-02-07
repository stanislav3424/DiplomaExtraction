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

    InitializeInventory(Row->InventorySize);
}

void UInventoryLogic::RemoveChildLogic(ULogicBase* ChildLogic)
{
    Super::RemoveChildLogic(ChildLogic);

    RemoveItemFromInventory(ChildLogic);
}

void UInventoryLogic::CheckValidInventorySize()
{
    if (IsValidInventorySize(this))
        return;
    InventorySize = FIntVector2(1, 1);
    UE_LOG(InitGameLogic, Warning, FILE_FUNC TEXT("Invalid inventory size detected. Resetting to default (1, 1)."))
}

void UInventoryLogic::InitializeInventory(FIntVector2 const& InitSize)
{
    InventorySize = InitSize;
    CheckValidInventorySize();
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

bool UInventoryLogic::IsPositionNotOccupied(FIntVector2 const& Position) const
{
    int32 Index = PositionToIndex(Position);
    if (InventoryGrid.IsValidIndex(Index))
        if (auto Item = InventoryGrid[Index])
            return false;
    return true;
}

bool UInventoryLogic::IsPositionValid(FIntVector2 const& Position) const
{
    int32 Index = PositionToIndex(Position);
    if (InventoryGrid.IsValidIndex(Index))
        return true;
    return false;
}

bool UInventoryLogic::CanPlaceItemAt(FIntVector2 const& Position, FIntVector2 const& ItemSize)
{
    FIntVector2 TopLeft     = Position;
    FIntVector2 BottomRight = Position + ItemSize - FIntVector2(1, 1);
    if (!IsPositionValid(TopLeft))
        return false;
    if (!IsPositionValid(BottomRight))
        return false;

    if (BottomRight.X >= InventorySize.X || BottomRight.Y >= InventorySize.Y)
        return false;

    if (!ArePositionsNotOccupied(GetPositions(Position, ItemSize)))
        return false;

    return true;
}

TArray<FIntVector2> UInventoryLogic::GetPositions(FIntVector2 const& Position, FIntVector2 const& ItemSize)
{
    TArray<FIntVector2> Positions;
    Positions.Reserve(ItemSize.X * ItemSize.Y);
    for (int32 X = 0; X < ItemSize.X; ++X)
        for (int32 Y = 0; Y < ItemSize.Y; ++Y)
            Positions.Add(Position + FIntVector2(X, Y));
    return Positions;
}

bool UInventoryLogic::ArePositionsNotOccupied(TArray<FIntVector2> const& Positions) const
{
    for (auto Position : Positions)
        if (!IsPositionNotOccupied(Position))
            return false;
    return true;
}

bool UInventoryLogic::CanAddItemToPosition(ULogicBase* Item, FIntVector2 const& Position, bool Rotation)
{
    if (!IsPositionNotOccupied(Position))
        return false;
    auto ItemLogic = Item->GetLogicComponent<UItemLogic>();
    if (!ItemLogic)
        return false;
    auto ItemSize = UItemLogic::GetRotationSize(ItemLogic->GetItemSize(), Rotation);
    if (!CanPlaceItemAt(Position, ItemSize))
        return false;
    return true;
}

bool UInventoryLogic::AddItemToPosition(ULogicBase* Item, FIntVector2 const& Position, bool Rotation)
{
    if (!CanAddItemToPosition(Item, Position, Rotation))
        return false;

    PlaceItemInInventory(Item, Position, Rotation);
    return true;
}

bool UInventoryLogic::AddItemToFirstAvailablePosition(ULogicBase* Item, bool PrioritizeRotation)
{
    auto AllPositionsInInventory = GetPositions(FIntVector2(0, 0), GetInventorySize());
    for (auto& Position : AllPositionsInInventory)
        if (CanAddItemToPosition(Item, Position, PrioritizeRotation))
        {
            PlaceItemInInventory(Item, Position, PrioritizeRotation);
            return true;
        }

    for (auto& Position : AllPositionsInInventory)
        if (CanAddItemToPosition(Item, Position, !PrioritizeRotation))
        {
            PlaceItemInInventory(Item, Position, !PrioritizeRotation);
            return true;
        }

    return false;
}

bool UInventoryLogic::RemoveItemFromInventory(ULogicBase* Item)
{
    if (!ItemsInInventory.Contains(Item))
        return false;

    ItemsInInventory.Remove(Item);

    for (auto& Slot : InventoryGrid)
        if (Slot == Item)
            Slot = nullptr;

    OnInventoryChanged.Broadcast();

    return true;
}

ULogicBase* UInventoryLogic::RemoveItemFromPosition(FIntVector2 const& Position)
{
    if (!IsPositionValid(Position))
        return nullptr;

    int32 Index = PositionToIndex(Position);
    if (InventoryGrid.IsValidIndex(Index))
        if (auto Item = InventoryGrid[Index])
        {
            RemoveItemFromInventory(Item);
            return Item;
        }

    return nullptr;
}

bool UInventoryLogic::IsItemInInventory(ULogicBase* Item)
{
    if (!Item)
        return false;
    return ItemsInInventory.Contains(Item);
}

void UInventoryLogic::PlaceItemInInventory(
    ULogicBase* Item, FIntVector2 const& Position, bool Rotation, bool bAddLogicComponent)
{
    if (!Item)
        return;

    auto ItemLogic = UItemLogic::GetItemLogicComponent(Item);
    if (!ItemLogic)
        return;

    if (bAddLogicComponent)
        AddLogicComponent(Item);

    ItemsInInventory.Add(Item, FItemInventoryData{ Position, Rotation });

    auto ItemSize = ItemLogic->GetItemSize();

    auto Positions = GetPositions(Position, UItemLogic::GetRotationSize(ItemSize, Rotation));
    for (auto& LocalPosition : Positions)
    {
        int32 Index = PositionToIndex(LocalPosition);
        if (InventoryGrid.IsValidIndex(Index))
            InventoryGrid[Index] = Item;
    }

    OnInventoryChanged.Broadcast();
}