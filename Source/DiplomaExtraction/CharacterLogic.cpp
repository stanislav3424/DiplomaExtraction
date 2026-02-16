// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterLogic.h"
#include "SpawnLibrary.h"
#include "EquipmentLogic.h"
#include "GameFramework/Character.h"
#include "MacroLibrary.h"
#include "Row.h"
#include "EnumLibrary.h"
#include "Components/CapsuleComponent.h"

void UCharacterLogic::InitializeRowHandler(FDataTableRowHandle const& InitRowHandle)
{
    Super::InitializeRowHandler(InitRowHandle);

    auto Row = InitRowHandle.GetRow<FCharacterLogicRow>(FILE_FUNC);
    if (!Row)
        return;
}

void UCharacterLogic::RemoveChildLogic(ULogicBase* ChildLogic)
{
    Super::RemoveChildLogic(ChildLogic);

    UnequipItem(ChildLogic);
}

void UCharacterLogic::OnGround()
{
}

void UCharacterLogic::SetSimulatePhysics()
{
    auto Character = Cast<ACharacter>(GetRepresentationActor());
    if (!Character)
        return;
    
    if (auto Controller = Character->GetController())
    {
        Controller->StopMovement();
        Controller->UnPossess();
    }

    if (auto CapsuleComponent = Character->GetCapsuleComponent())
    {
        CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }

    if (auto Mesh = Character->GetMesh())
    {
        Mesh->SetCollisionProfileName(TEXT("Ragdoll"));
        Mesh->SetSimulatePhysics(true);
        Mesh->WakeAllRigidBodies();
        Mesh->bBlendPhysics = true;
    }
}

void UCharacterLogic::RepresentationActorChanged(AActor* NewRepresentationActor)
{
    Super::RepresentationActorChanged(NewRepresentationActor);

    for (auto Slot : EquippedItems)
        SetVisualization(Slot.Key, Slot.Value);
}

bool UCharacterLogic::EquipItem(ULogicBase* Item)
{
    if (!IsValidEquippedItem(Item))
        return false;

    auto ItemSlot = GetEquipmentSlot(Item);

    return EquipItem(ItemSlot, Item);
}

bool UCharacterLogic::EquipItem(EEquipmentSlot const& TargetSlot, ULogicBase* Item)
{
    if (!IsValidEquippedItem(Item))
        return false;

    if (!CanEquipItem(TargetSlot, Item))
        return false;

    AddLogicComponent(Item);

    EquippedItems.Add(TargetSlot, Item);
    OnEquipmentChanged.Broadcast();

    SetVisualization(TargetSlot, Item);

    return true;
}

void UCharacterLogic::SetVisualization(const EEquipmentSlot& TargetSlot, ULogicBase* Item)
{
    if (!Item)
        return;

    auto Character = Cast<ACharacter>(GetRepresentationActor());
    if (!Character)
        return;

    auto Mesh = Character->GetMesh();
    if (!Mesh)
        return;

    auto Name      = UEnumLibrary::EnumToName<EEquipmentSlot>(TargetSlot);
    auto Transform = Mesh->GetSocketTransform(Name);

    auto Actor = Item->SpawnRepresentationActor(Transform.GetLocation(), Transform.Rotator());
    if (!Actor)
        return;

    TArray<UPrimitiveComponent*> Primitives;
    Actor->GetComponents<UPrimitiveComponent>(Primitives);
    for (auto Primitive : Primitives)
    {
        Primitive->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        Primitive->SetGenerateOverlapEvents(false);
    }

    Actor->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, Name);
}

bool UCharacterLogic::CanEquipItem(EEquipmentSlot const& TargetSlot, ULogicBase* Item)
{
    if (!IsValidEquippedItem(Item))
        return false;

    auto ItemSlot = GetEquipmentSlot(Item);

    // A temporary option
    if (TargetSlot == EEquipmentSlot::BackWeapon && ItemSlot == EEquipmentSlot::Hands)
        return !EquippedItems.Contains(TargetSlot);
    //

    if (ItemSlot != TargetSlot)
        return false;

    return !EquippedItems.Contains(TargetSlot);
}

ULogicBase* UCharacterLogic::UnequipItem(ULogicBase* Item)
{
    if (!Item)
        return nullptr;

    for (auto Slot : EquippedItems)
        if (Slot.Value == Item)
        {
            EquippedItems.Remove(Slot.Key);
            OnEquipmentChanged.Broadcast();
            return Item;
        }
   
    return nullptr;
}

ULogicBase* UCharacterLogic::UnequipItem(EEquipmentSlot const& TargetSlot)
{
    auto Item = GetEquippedItem(TargetSlot);
    if (!Item)
        return nullptr;

    return UnequipItem(Item);
}

ULogicBase* UCharacterLogic::GetEquippedItem(EEquipmentSlot const& TargetSlot) const
{
    if (!EquippedItems.Contains(TargetSlot))
        return nullptr;

    auto Item = EquippedItems[TargetSlot];

    return Item;
}

bool UCharacterLogic::IsValidEquippedItem(ULogicBase* Item)
{
    if (!Item)
        return false;

    if (GetEquipmentSlot(Item) == EEquipmentSlot::None)
        return false;

    return true;
}


EEquipmentSlot UCharacterLogic::GetEquipmentSlot(ULogicBase* Item)
{
    auto EquipmentLogic = UEquipmentLogic::GetEquipmentLogicComponent(Item);
    if (!EquipmentLogic)
        return EEquipmentSlot::None;

    return EquipmentLogic->GetEquipmentSlot();
}
