// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LogicBase.h"
#include "ItemLogic.generated.h"

UCLASS(Abstract, NotBlueprintable)
class DIPLOMAEXTRACTION_API UItemLogic : public ULogicBase
{
    GENERATED_BODY()

    // Initialize
public:
    virtual void InitializeRowHandler(FDataTableRowHandle const& InitRowHandle) override;

    // Item Management
public:
    FIntVector2 GetItemSize() const { return ItemSize; }

    static FIntVector2 GetRotationSize(FIntVector2 const& OriginalSize, bool Rotation);
    static bool        IsValidItemSize(ULogicBase* Item);

private:
    void CheckValidItemSize();

    FIntVector2 ItemSize = FIntVector2(1, 1);
};
