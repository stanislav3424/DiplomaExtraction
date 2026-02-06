// Fill out your copyright notice in the Description page of Project Settings.

#include "UW_Equipment.h"
#include "UW_Item.h"
#include "Row.h"
#include "CharacterLogic.h"
#include "MacroLibrary.h"
#include "LogicLibrary.h"
#include "Blueprint/DragDropOperation.h"

UUW_Equipment::UUW_Equipment()
{
    bIsAutoInitializeChildLogic = false;
    EquipmentSlot               = EEquipmentSlot::None;
}

void UUW_Equipment::LogicChanged(ULogicBase* OldLogic, ULogicBase* NewLogic)
{
    Super::LogicChanged(OldLogic, NewLogic);

    if (EquipmentSlot == EEquipmentSlot::None)
        return;

    if (auto CharacterLogic = Cast<UCharacterLogic>(OldLogic))
    {
        CharacterLogic->OnEquipmentChanged.RemoveDynamic(this, &UUW_Equipment::OnEquipmentChanged);
    }

    if (auto CharacterLogic = Cast<UCharacterLogic>(NewLogic))
    {
        CharacterLogic->OnEquipmentChanged.AddUniqueDynamic(this, &UUW_Equipment::OnEquipmentChanged);
        CharacterLogic->OnEquipmentChanged.Broadcast();
    }
}

bool UUW_Equipment::NativeOnDrop(
    const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
    if (!InOperation)
        return false;
    auto CharacterLogic = Cast<UCharacterLogic>(GetLogic_Implementation());
    if (!CharacterLogic)
        return false;

    auto Payload = Cast<ULogicBase>(InOperation->Payload);
    if (!Payload)
        return false;

    return CharacterLogic->EquipItem(EquipmentSlot, Payload);
}

void UUW_Equipment::OnEquipmentChanged()
{
    auto CharacterLogic = Cast<UCharacterLogic>(GetLogic_Implementation());
    if (!CharacterLogic)
        return;
    auto Item = CharacterLogic->GetEquippedItem(EquipmentSlot);

    if (ItemWidget)
        ItemWidget->SetVisibility(Item ? ESlateVisibility::Visible : ESlateVisibility::Hidden);

    ULogicLibrary::SetLogic(ItemWidget, Item);
}
