// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UW_Dialog.h"
#include "UW_MainMenu.generated.h"

class USlider;

UCLASS(Abstract, Blueprintable)
class DIPLOMAEXTRACTION_API UUW_MainMenu : public UUW_Dialog
{
	GENERATED_BODY()

protected:
    virtual void NativeOnInitialized() override;

    virtual void StartOpen();
    virtual void StartClose();
    virtual void FinishOpen();
    virtual void FinishClose();

    void LoadGraphicsSettings();
    void ApplyGraphicsSettings();

    UFUNCTION() void OnViewDistanceChanged(float Value);
    UFUNCTION() void OnShadowChanged(float Value);
    UFUNCTION() void OnGlobalIlluminationChanged(float Value);
    UFUNCTION() void OnReflectionChanged(float Value);
    UFUNCTION() void OnAntiAliasingChanged(float Value);
    UFUNCTION() void OnTextureChanged(float Value);
    UFUNCTION() void OnVisualEffectsChanged(float Value);
    UFUNCTION() void OnPostProcessingChanged(float Value);
    UFUNCTION() void OnFoliageChanged(float Value);
    UFUNCTION() void OnShadingChanged(float Value);

    UPROPERTY(meta = (BindWidget)) USlider* Slider_ViewDistance;
    UPROPERTY(meta = (BindWidget)) USlider* Slider_Shadow;
    UPROPERTY(meta = (BindWidget)) USlider* Slider_GlobalIllumination;
    UPROPERTY(meta = (BindWidget)) USlider* Slider_Reflection;
    UPROPERTY(meta = (BindWidget)) USlider* Slider_AntiAliasing;
    UPROPERTY(meta = (BindWidget)) USlider* Slider_Texture;
    UPROPERTY(meta = (BindWidget)) USlider* Slider_VisualEffects;
    UPROPERTY(meta = (BindWidget)) USlider* Slider_PostProcessing;
    UPROPERTY(meta = (BindWidget)) USlider* Slider_Foliage;
    UPROPERTY(meta = (BindWidget)) USlider* Slider_Shading;

    int32 ViewDistanceQuality;
    int32 ShadowQuality;
    int32 GlobalIlluminationQuality;
    int32 ReflectionQuality;
    int32 AntiAliasingQuality;
    int32 TextureQuality;
    int32 VisualEffectsQuality;
    int32 PostProcessingQuality;
    int32 FoliageQuality;
    int32 ShadingQuality;
};
