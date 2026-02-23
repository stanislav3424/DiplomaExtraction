// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "MacroLibrary.h"
#include "SpawnLibrary.h"
#include "LogicBase.h"
#include "StaminaLogic.h"
#include "WeaponLogic.h"
#include "CharacterLogic.h"
#include "Row.h"

APlayerCharacter::APlayerCharacter()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(GetRootComponent());
    SpringArm->bDoCollisionTest         = false;
    SpringArm->bEnableCameraLag         = true;
    SpringArm->bEnableCameraRotationLag = true;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void APlayerCharacter::SetLogic_Implementation(ULogicBase* NewLogic)
{
    Super::SetLogic_Implementation(NewLogic);

    AddMappingContext();
    SetActorTickEnabled(true);
}

void APlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    TargetArmLength = SpringArm ? SpringArm->TargetArmLength : 1000.f;
}

void APlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    ZoomTick(DeltaTime);
    RotateTick(DeltaTime);
    RotatePawnToCursor();
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    CHECK_VAR_RETURN(EnhancedInputComponent)

    CHECK_VAR_RETURN(MoveInputAction)
    EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::OnMove);
    CHECK_VAR_RETURN(RotateInputAction)
    EnhancedInputComponent->BindAction(RotateInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::OnRotate);
    CHECK_VAR_RETURN(ZoomInputAction)
    EnhancedInputComponent->BindAction(ZoomInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::OnZoom);
    
    CHECK_VAR_RETURN(ShiftInputAction)
    EnhancedInputComponent->BindAction(ShiftInputAction, ETriggerEvent::Started, this, &APlayerCharacter::OnShift);
    CHECK_VAR_RETURN(ShiftInputAction)
    EnhancedInputComponent->BindAction(ShiftInputAction, ETriggerEvent::Completed, this, &APlayerCharacter::OnShift);
    CHECK_VAR_RETURN(ShootInputAction)
    EnhancedInputComponent->BindAction(ShootInputAction, ETriggerEvent::Started, this, &APlayerCharacter::OnShoot);
    CHECK_VAR_RETURN(ShootInputAction)
    EnhancedInputComponent->BindAction(ShootInputAction, ETriggerEvent::Completed, this, &APlayerCharacter::OnShoot);
    CHECK_VAR_RETURN(ReloadInputAction)
    EnhancedInputComponent->BindAction(ReloadInputAction, ETriggerEvent::Started, this, &APlayerCharacter::OnReload);
    CHECK_VAR_RETURN(HealingInputAction)
    EnhancedInputComponent->BindAction(HealingInputAction, ETriggerEvent::Started, this, &APlayerCharacter::OnHealing);
}

void APlayerCharacter::OnMove(const FInputActionValue& Value)
{
    auto MoveInput = Value.Get<FVector2D>();

    AddMovementInput(GetActorForwardVector(), MoveInput.Y);
    AddMovementInput(GetActorRightVector(), MoveInput.X);
}

void APlayerCharacter::OnRotate(const FInputActionValue& Value)
{
    auto RotateInput = Value.Get<float>();

    if (SpringArm)
        SpringArm->AddWorldRotation(FRotator(0.f, RotateInput * RotateSpeed, 0.f));
}

void APlayerCharacter::OnZoom(const FInputActionValue& Value)
{
    auto ZoomInput = Value.Get<float>();

    if (SpringArm)
        TargetArmLength = FMath::Clamp(TargetArmLength + ZoomInput * ZoomMultiplier, MinZoom, MaxZoom);
}

void APlayerCharacter::OnShift(const FInputActionValue& Value)
{
    auto ShiftInput = Value.Get<bool>();

    auto CharacterLogic = Cast<UCharacterLogic>(GetLogic_Implementation());
    CHECK_VAR_RETURN(CharacterLogic)

    CharacterLogic->OnShift(ShiftInput);
}

void APlayerCharacter::OnShoot(const FInputActionValue& Value)
{
    auto ShootInput = Value.Get<bool>();

    auto CharacterLogic = Cast<UCharacterLogic>(GetLogic_Implementation());
    CHECK_VAR_RETURN(CharacterLogic)

    CharacterLogic->OnShoot(ShootInput);
}

void APlayerCharacter::OnReload(const FInputActionValue& Value)
{
    auto CharacterLogic = Cast<UCharacterLogic>(GetLogic_Implementation());
    CHECK_VAR_RETURN(CharacterLogic)

    CharacterLogic->OnReload();
}

void APlayerCharacter::OnHealing(const FInputActionValue& Value)
{
    auto CharacterLogic = Cast<UCharacterLogic>(GetLogic_Implementation());
    CHECK_VAR_RETURN(CharacterLogic)

    CharacterLogic->OnHealing();
}

void APlayerCharacter::ZoomTick(float DeltaTime)
{
    if (SpringArm)
        SpringArm->TargetArmLength =
            FMath::FInterpConstantTo(SpringArm->TargetArmLength, TargetArmLength, DeltaTime, ZoomSpeed);
}

void APlayerCharacter::RotateTick(float DeltaTime)
{
}

void APlayerCharacter::RotatePawnToCursor()
{
    auto PlayerController = GetController<APlayerController>();
    if (!PlayerController)
        return;

    FHitResult HitResult;
    if (PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult))
    {
        FVector Direction = HitResult.Location - GetActorLocation();
        Direction.Z       = 0.f;
        Direction.Normalize();
        SetActorRotation(FRotator(0.f, Direction.Rotation().Yaw, 0.f));
    }
}

void APlayerCharacter::AddMappingContext()
{
    CHECK_VAR_RETURN(CameraInputMappingContext)   
    CHECK_VAR_RETURN(ControlPawnInputMappingContext)   

    auto World = GetWorld();
    if (!World)
        return;
    auto LocalPlayer = World->GetFirstLocalPlayerFromController();
    if (!LocalPlayer)
        return;
    auto EnhancedInputLocalPlayerSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
    if (!EnhancedInputLocalPlayerSubsystem)
        return;
    EnhancedInputLocalPlayerSubsystem->AddMappingContext(CameraInputMappingContext, 0);
    EnhancedInputLocalPlayerSubsystem->AddMappingContext(ControlPawnInputMappingContext, 0);
}

    