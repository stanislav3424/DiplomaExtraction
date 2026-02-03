// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UW_Base.h"
#include "UW_Item.generated.h"

class USizeBox;

UCLASS(Abstract, Blueprintable)
class DIPLOMAEXTRACTION_API UUW_Item : public UUW_Base
{
    GENERATED_BODY()

protected:
    virtual void LogicChanged(ULogicBase* OldLogic, ULogicBase* NewLogic);
    virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual void   NativeOnDragDetected(
          const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

    UPROPERTY(meta = (BindWidget))
    USizeBox* SizeBox;

private:
    bool bIsRotated = false;

public:
    UFUNCTION()
    void SwitchRotation();
    void SetDragSettings();
    void SetRotation(bool bRotated);
    void SetAutoSize();
    void SetSizeBoxSize(float Width, float Height);
    void ClearSizeBoxSize();
};
