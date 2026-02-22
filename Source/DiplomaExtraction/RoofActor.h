// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoofActor.generated.h"

enum class EStatusGame : uint8;

UCLASS()
class DIPLOMAEXTRACTION_API ARoofActor : public AActor
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnStatusGameChanged(EStatusGame const& NewStatusGame);

	void SetVisibility(bool bNewVisibility);

	bool bVisibility = true;
};
