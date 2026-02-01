// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InitRowHandle.generated.h"


UCLASS(NotBlueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DIPLOMAEXTRACTION_API UInitRowHandle : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "InitRowHandle")
	FDataTableRowHandle InitRowHandle;
};
