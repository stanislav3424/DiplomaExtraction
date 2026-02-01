// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IconRendering.generated.h"

class USceneCaptureComponent2D;
class USpringArmComponent;
class ULogicBase;

UCLASS(Blueprintable, Abstract)
class DIPLOMAEXTRACTION_API AIconRendering : public AActor
{
    GENERATED_BODY()

public:
    AIconRendering();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaSeconds) override;

protected:
    UPROPERTY(VisibleAnywhere)
    USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere)
    USceneCaptureComponent2D* SceneCapture;

    UPROPERTY(EditDefaultsOnly, Category = "IconRendering")
    FName MIDTextureParameterName = TEXT("IconTexture");

    UPROPERTY(EditDefaultsOnly, Category = "IconRendering")
    FName MIDTextureReadyParameterName = TEXT("IsTextureReady");

    UPROPERTY(Transient)
    AActor* SpawnedRepresentationActor;

    TMap<FName, TPair<UTextureRenderTarget2D*, bool>>                CacheTextures;
    TMap<UTextureRenderTarget2D*, TArray<UMaterialInstanceDynamic*>> WaitingMIDs;
    TQueue<TPair<FDataTableRowHandle, UTextureRenderTarget2D*>>      QueueRender;

    float WarmupTime = 5.0f;

    bool WarmupCapture(float DeltaSeconds);
    UTextureRenderTarget2D* GetNewRenderTarget();
    void SettingCamera(AActor* Actor);
    void SetLightingChannels(AActor* Actor);
    void GetIcon_(ULogicBase* Logic, UMaterialInstanceDynamic* MID);

public:
    static void GetIcon(ULogicBase* Logic, UMaterialInstanceDynamic* MID);
};
