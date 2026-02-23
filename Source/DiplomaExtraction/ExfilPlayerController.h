// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ExfilPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryItemRotate);

class UInputMappingContext;
class UInputAction;
class ULevelSequence;
class ULevelSequencePlayer;

struct FInputActionValue;

UCLASS(Abstract, Blueprintable)
class DIPLOMAEXTRACTION_API AExfilPlayerController : public APlayerController
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void         OnStatusGameChanged(EStatusGame const& NewStatusGame);
    void         AddMappingContext();
    void         RemoveMappingContext();
    virtual void SetupInputComponent() override;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputMappingContext* UserInterfaceInputMappingContext;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* MainMenuInputAction;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* PawnInfoInputAction;

    void OnMainMenu(FInputActionValue const& Value);
    void OnPawnInfo(FInputActionValue const& Value);

    void EnterCinematicMode();
    void EnterDefaultMode();
    void EnterSpectatorMode();

    UFUNCTION()
    void PlayLevelSequence();
    void StopLevelSequence();

    UFUNCTION()
    void PlayGameEndLevelSequence();

    UFUNCTION()
    void GameEnd();

    UPROPERTY(Transient)
    ULevelSequencePlayer* LevelSequencePlayer;

    UPROPERTY(EditDefaultsOnly, Category = "LevelSequence")
    TArray<ULevelSequence*> ArrLevelSequence;

    UPROPERTY(EditDefaultsOnly, Category = "LevelSequence")
    ULevelSequence* GameEndLevelSequence;

public:
    FOnInventoryItemRotate OnInventoryItemRotate;
};
