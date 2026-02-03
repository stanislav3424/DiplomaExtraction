// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ExfilPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryItemRotate);

class UInputMappingContext;
class UInputAction;

struct FInputActionValue;

UCLASS(Abstract, Blueprintable)
class DIPLOMAEXTRACTION_API AExfilPlayerController : public APlayerController
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
    void         AddMappingContext();
    virtual void SetupInputComponent() override;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputMappingContext* UserInterfaceInputMappingContext;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* MainMenuInputAction;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* PawnInfoInputAction;

    void OnMainMenu(FInputActionValue const& Value);
    void OnPawnInfo(FInputActionValue const& Value);

public:
    FOnInventoryItemRotate OnInventoryItemRotate;
};
