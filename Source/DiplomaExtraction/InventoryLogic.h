#pragma once

#include "CoreMinimal.h"
#include "LogicBase.h"
#include "InventoryLogic.generated.h"

USTRUCT(BlueprintType)
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

private:
    void        CheckValidInventorySize();
    void        InitializeInventory();
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
    bool        CanAddItemToPosition(ULogicBase* Item, FIntVector2 const& Position, bool Rotation = false);
    bool        AddItemToPosition(ULogicBase* Item, FIntVector2 const& Position, bool Rotation = false);
    bool        AddItemToFirstAvailablePosition(ULogicBase* Item, bool PrioritizeRotation = false);
    bool        RemoveItemFromInventory(ULogicBase* Item);
    ULogicBase* RemoveItemFromPosition(FIntVector2 const& Position);
    bool        GetItemInventoryData(ULogicBase* Item, FItemInventoryData& OutItemInventoryData) const;
    FIntVector2 GetInventorySize() const { return InventorySize; }

private:
    void PlaceItemInInventory(ULogicBase* Item, FIntVector2 const& Position, bool Rotation = false);

    FIntVector2 InventorySize = FIntVector2(1, 1);

    UPROPERTY(Transient)
    TArray<ULogicBase*> InventoryGrid;

    UPROPERTY(Transient)
    TMap<ULogicBase*, FItemInventoryData> ItemsInInventory;
};
