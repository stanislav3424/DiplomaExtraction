// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

struct FInputActionValue;

UCLASS(Abstract, Blueprintable)
class DIPLOMAEXTRACTION_API APlayerCharacter : public ACharacterBase
{
    GENERATED_BODY()

    APlayerCharacter();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(VisibleAnywhere)
    USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere)
    UCameraComponent* Camera;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputMappingContext* CameraInputMappingContext;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* RotateInputAction;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* ZoomInputAction;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputMappingContext* ControlPawnInputMappingContext;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* MoveInputAction;

    UPROPERTY(EditDefaultsOnly, Category = "Camera")
    float RotateSpeed = 1.f;

    UPROPERTY(EditDefaultsOnly, Category = "Camera")
    float ZoomMultiplier = 100.f;

    UPROPERTY(EditDefaultsOnly, Category = "Camera")
    float ZoomSpeed = 2500.f;

    UPROPERTY(EditDefaultsOnly, Category = "Camera")
    float MinZoom = 300.f;

    UPROPERTY(EditDefaultsOnly, Category = "Camera")
    float MaxZoom = 5000.f;

    float TargetArmLength;
    float TargetYaw;

    void OnMove(const FInputActionValue& Value);
    void OnRotate(const FInputActionValue& Value);
    void OnZoom(const FInputActionValue& Value);

    void ZoomTick(float DeltaTime);
    void RotateTick(float DeltaTime);
    void RotatePawnToCursor();

    void AddMappingContext();
};
