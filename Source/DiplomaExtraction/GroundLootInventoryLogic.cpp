// Fill out your copyright notice in the Description page of Project Settings.

#include "GroundLootInventoryLogic.h"

void UGroundLootInventoryLogic::InitSize()
{
    InitializeInventory(FIntVector2(8, 12));
}

bool UGroundLootInventoryLogic::CanAddItemToPosition(ULogicBase* Item, FIntVector2 const& Position, bool Rotation)
{
    if (Item)
        if (Item->GetOwnerLogic())
        {
            return true;
        }
        else if (!IsItemInInventory(Item))
            return Super::CanAddItemToPosition(Item, Position, Rotation);

    return false;
}

void UGroundLootInventoryLogic::PlaceItemInInventory(
    ULogicBase* Item, FIntVector2 const& Position, bool Rotation, bool bAddLogicComponent)
{

    if (Item)
        if (Item->GetOwnerLogic())
        {
            FVector  SpawnLocation = FVector(0.f, 0.f, 50.f);
            FRotator SpawnRotation = FRotator::ZeroRotator; 
            if (auto Logic = GetOwnerLogic())
                if (auto ActorOwner = Logic->GetRepresentationActor())
                {
                    SpawnLocation += ActorOwner->GetActorLocation();
                    SpawnRotation = ActorOwner->GetActorRotation();
                    if (auto Actor = Item->DropToGround(SpawnLocation, SpawnRotation))
                    {
                        //ActorOwner->UpdateOverlaps();
                        //Actor->UpdateOverlaps();
                    }
                }


            return;
        }
        else
        {
            Super::PlaceItemInInventory(Item, Position, Rotation, false);
        }

    return;
}
