#pragma once

#include "CoreMinimal.h"
#include "LogicBase.h"
#include "InventoryLogic.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChanged);

USTRUCT(Blueprintable)
struct FItemInventoryData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FIntVector2 PositionItem = FIntVector2(0, 0);

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool RotationItem = false;
};

class UItemLogic;

UCLASS(NotBlueprintable)
class DIPLOMAEXTRACTION_API UInventoryLogic : public ULogicBase
{
    GENERATED_BODY()

    // Initialize
public:
    virtual void InitializeRowHandler(FDataTableRowHandle const& InitRowHandle) override;
    virtual void RemoveChildLogic(ULogicBase* ChildLogic);

private:
    void CheckValidInventorySize();

protected:
    void InitializeInventory(FIntVector2 const& InitSize);

private:
    static bool IsValidInventorySize(ULogicBase* Item);

    // Inventory Functionality
private:
    int32               PositionToIndex(FIntVector2 const& Position) const;
    FIntVector2         IndexToPosition(int32 Index);
    bool                IsPositionNotOccupied(FIntVector2 const& Position) const;
    bool                IsPositionValid(FIntVector2 const& Position) const;
    bool                CanPlaceItemAt(FIntVector2 const& Position, FIntVector2 const& ItemSize);
    TArray<FIntVector2> GetPositions(FIntVector2 const& Position, FIntVector2 const& ItemSize);
    bool                ArePositionsNotOccupied(TArray<FIntVector2> const& Positions) const;

public:
    virtual bool CanAddItemToPosition(ULogicBase* Item, FIntVector2 const& Position, bool Rotation = false);
    bool         AddItemToPosition(ULogicBase* Item, FIntVector2 const& Position, bool Rotation = false);
    bool         AddItemToFirstAvailablePosition(ULogicBase* Item, bool PrioritizeRotation = false);
    bool         RemoveItemFromInventory(ULogicBase* Item);
    ULogicBase*  RemoveItemFromPosition(FIntVector2 const& Position);
    FIntVector2  GetInventorySize() const { return InventorySize; }
    TMap<ULogicBase*, FItemInventoryData> GetItemsInInventory() { return ItemsInInventory; }

    FOnInventoryChanged OnInventoryChanged;

protected:
    virtual void PlaceItemInInventory(ULogicBase* Item, FIntVector2 const& Position, bool Rotation = false);

private:
    FIntVector2 InventorySize = FIntVector2(1, 1);

    UPROPERTY(Transient)
    TArray<ULogicBase*> InventoryGrid;

    UPROPERTY(Transient)
    TMap<ULogicBase*, FItemInventoryData> ItemsInInventory;
};
