// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UW_Base.h"
#include "UW_Inventory.generated.h"

class UUW_Item;
class UCanvasPanel;
class UUW_InventoryGrid;
class UInventoryLogic;
class USizeBox;
class UImage;

UCLASS(Abstract, Blueprintable)
class DIPLOMAEXTRACTION_API UUW_Inventory : public UUW_Base
{
    GENERATED_BODY()

    UUW_Inventory();

protected:
    virtual void LogicChanged(ULogicBase* OldLogic, ULogicBase* NewLogic);
    virtual bool NativeOnDrop(
        const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
    virtual void NativeOnDragEnter(
        const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
    virtual bool NativeOnDragOver(
        const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
    virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

    UFUNCTION()
    void OnInventoryChanged();

    void SetGridPreviewEnabled(bool bEnabled);

    void UpdateGridPreviewPosition(const FGeometry& InGeometry, const FVector2D& MousePosition, ULogicBase* Item);

    FIntVector2 GetAdjustedPositionForItem(
        const FGeometry& InGeometry, const FVector2D& MousePosition, ULogicBase* Item) const;

    UPROPERTY(Transient)
    TArray<UUW_Item*> ItemWidgets;

    UPROPERTY(EditDefaultsOnly, Category = "ItemWidgetClass")
    TSubclassOf<UUW_Item> ItemWidgetClass;

    UPROPERTY(meta = (BindWidget))
    UCanvasPanel* CanvasPanel;

    UPROPERTY(meta = (BindWidget))
    UUW_InventoryGrid* InventoryGrid;

    UPROPERTY(meta = (BindWidget))
    USizeBox* SizeBox;

    UPROPERTY(Transient)
    UImage* GridPreviewImage;

    UPROPERTY(EditDefaultsOnly, Category = "GridPreview")
    UMaterialInterface* GridPreviewMaterial;

    UPROPERTY(EditDefaultsOnly, Category = "GridPreview")
    FName PreviewOverlayParameterName = FName(TEXT("CanPlace"));

};
