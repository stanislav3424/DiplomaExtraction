// Fill out your copyright notice in the Description page of Project Settings.

#include "UW_Equipment.h"
#include "UW_Item.h"
#include "Row.h"
#include "CharacterLogic.h"
#include "MacroLibrary.h"
#include "LogicLibrary.h"

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

    auto CharacterLogic = Cast<UCharacterLogic>(NewLogic);
    if (!CharacterLogic)
        return;

    CharacterLogic->OnEquipmentChanged.AddUniqueDynamic(this, &UUW_Equipment::OnEquipmentChanged);
    CharacterLogic->OnEquipmentChanged.Broadcast();
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
