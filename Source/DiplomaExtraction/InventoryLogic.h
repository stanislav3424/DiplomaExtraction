#pragma once

#include "CoreMinimal.h"
#include "LogicBase.h"
#include "InventoryLogic.generated.h"

UCLASS(Abstract, NotBlueprintable)
class DIPLOMAEXTRACTION_API UInventoryLogic : public ULogicBase
{
    GENERATED_BODY()

public:
    virtual void InitializeRowHandler(FDataTableRowHandle const& InitRowHandle) override;

    // Inventory implementation reserved for future
};
