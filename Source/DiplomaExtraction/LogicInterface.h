// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LogicInterface.generated.h"

class ULogicBase;

UINTERFACE(MinimalAPI)
class ULogicInterface : public UInterface
{
	GENERATED_BODY()
};

class DIPLOMAEXTRACTION_API ILogicInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Logic")
	ULogicBase* GetLogic();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Logic")
	void SetLogic(ULogicBase* NewLogic);
};
