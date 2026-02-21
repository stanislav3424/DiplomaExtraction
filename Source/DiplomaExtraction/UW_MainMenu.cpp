// Fill out your copyright notice in the Description page of Project Settings.

#include "UW_MainMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Slider.h"
#include "ExfilGameMode.h"
#include "GameFramework/GameUserSettings.h"

void UUW_MainMenu::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    
    LoadGraphicsSettings();
}

void UUW_MainMenu::StartOpen()
{
    Super::StartOpen();

    auto GameMode = Cast<AExfilGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    if (!GameMode)
        return;

    GameMode->SetPauseGame(true);
}

void UUW_MainMenu::StartClose()
{
    Super::StartClose();

}

void UUW_MainMenu::FinishOpen()
{
    Super::FinishOpen();

}

void UUW_MainMenu::FinishClose()
{
    Super::FinishClose();

    auto GameMode = Cast<AExfilGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
    if (!GameMode)
        return;

    GameMode->SetPauseGame(false);
}

void UUW_MainMenu::LoadGraphicsSettings()
{
    auto Settings = GEngine->GetGameUserSettings();
    if (!Settings)
        return;

    ViewDistanceQuality       = Settings->GetViewDistanceQuality();
    ShadowQuality             = Settings->GetShadowQuality();
    GlobalIlluminationQuality = Settings->GetGlobalIlluminationQuality();
    ReflectionQuality         = Settings->GetReflectionQuality();
    AntiAliasingQuality       = Settings->GetAntiAliasingQuality();
    TextureQuality            = Settings->GetTextureQuality();
    VisualEffectsQuality      = Settings->GetVisualEffectQuality();
    PostProcessingQuality     = Settings->GetPostProcessingQuality();
    FoliageQuality            = Settings->GetFoliageQuality();
    ShadingQuality            = Settings->GetShadingQuality();

    if (Slider_ViewDistance)
    {
        Slider_ViewDistance->SetValue(static_cast<float>(ViewDistanceQuality));
        Slider_ViewDistance->OnValueChanged.AddDynamic(this, &UUW_MainMenu::OnViewDistanceChanged);
    }
    if (Slider_Shadow)
    {
        Slider_Shadow->SetValue(static_cast<float>(ShadowQuality));
        Slider_Shadow->OnValueChanged.AddDynamic(this, &UUW_MainMenu::OnShadowChanged);
    }
    if (Slider_GlobalIllumination)
    {
        Slider_GlobalIllumination->SetValue(static_cast<float>(GlobalIlluminationQuality));
        Slider_GlobalIllumination->OnValueChanged.AddDynamic(this, &UUW_MainMenu::OnGlobalIlluminationChanged);
    }
    if (Slider_Reflection)
    {
        Slider_Reflection->SetValue(static_cast<float>(ReflectionQuality));
        Slider_Reflection->OnValueChanged.AddDynamic(this, &UUW_MainMenu::OnReflectionChanged);
    }
    if (Slider_AntiAliasing)
    {
        Slider_AntiAliasing->SetValue(static_cast<float>(AntiAliasingQuality));
        Slider_AntiAliasing->OnValueChanged.AddDynamic(this, &UUW_MainMenu::OnAntiAliasingChanged);
    }
    if (Slider_Texture)
    {
        Slider_Texture->SetValue(static_cast<float>(TextureQuality));
        Slider_Texture->OnValueChanged.AddDynamic(this, &UUW_MainMenu::OnTextureChanged);
    }
    if (Slider_VisualEffects)
    {
        Slider_VisualEffects->SetValue(static_cast<float>(VisualEffectsQuality));
        Slider_VisualEffects->OnValueChanged.AddDynamic(this, &UUW_MainMenu::OnVisualEffectsChanged);
    }
    if (Slider_PostProcessing)
    {
        Slider_PostProcessing->SetValue(static_cast<float>(PostProcessingQuality));
        Slider_PostProcessing->OnValueChanged.AddDynamic(this, &UUW_MainMenu::OnPostProcessingChanged);
    }
    if (Slider_Foliage)
    {
        Slider_Foliage->SetValue(static_cast<float>(FoliageQuality));
        Slider_Foliage->OnValueChanged.AddDynamic(this, &UUW_MainMenu::OnFoliageChanged);
    }
    if (Slider_Shading)
    {
        Slider_Shading->SetValue(static_cast<float>(ShadingQuality));
        Slider_Shading->OnValueChanged.AddDynamic(this, &UUW_MainMenu::OnShadingChanged);
    }
}

void UUW_MainMenu::ApplyGraphicsSettings()
{
    auto Settings = GEngine->GetGameUserSettings();
    if (!Settings)
        return;

    Settings->SetViewDistanceQuality(ViewDistanceQuality);
    Settings->SetShadowQuality(ShadowQuality);
    Settings->SetGlobalIlluminationQuality(GlobalIlluminationQuality);
    Settings->SetReflectionQuality(ReflectionQuality);
    Settings->SetAntiAliasingQuality(AntiAliasingQuality);
    Settings->SetTextureQuality(TextureQuality);
    Settings->SetVisualEffectQuality(VisualEffectsQuality);
    Settings->SetPostProcessingQuality(PostProcessingQuality);
    Settings->SetFoliageQuality(FoliageQuality);
    Settings->SetShadingQuality(ShadingQuality);

    Settings->ApplySettings(true);
}

void UUW_MainMenu::OnViewDistanceChanged(float Value)
{
    ViewDistanceQuality = FMath::Clamp(FMath::RoundToInt(Value), 0, 4);
    ApplyGraphicsSettings();
}

void UUW_MainMenu::OnShadowChanged(float Value)
{
    ShadowQuality = FMath::Clamp(FMath::RoundToInt(Value), 0, 4);
    ApplyGraphicsSettings();
}

void UUW_MainMenu::OnGlobalIlluminationChanged(float Value)
{
    GlobalIlluminationQuality = FMath::Clamp(FMath::RoundToInt(Value), 0, 4);
    ApplyGraphicsSettings();
}

void UUW_MainMenu::OnReflectionChanged(float Value)
{
    ReflectionQuality = FMath::Clamp(FMath::RoundToInt(Value), 0, 4);
    ApplyGraphicsSettings();
}

void UUW_MainMenu::OnAntiAliasingChanged(float Value)
{
    AntiAliasingQuality = FMath::Clamp(FMath::RoundToInt(Value), 0, 4);
    ApplyGraphicsSettings();
}

void UUW_MainMenu::OnTextureChanged(float Value)
{
    TextureQuality = FMath::Clamp(FMath::RoundToInt(Value), 0, 4);
    ApplyGraphicsSettings();
}

void UUW_MainMenu::OnVisualEffectsChanged(float Value)
{
    VisualEffectsQuality = FMath::Clamp(FMath::RoundToInt(Value), 0, 4);
    ApplyGraphicsSettings();
}

void UUW_MainMenu::OnPostProcessingChanged(float Value)
{
    PostProcessingQuality = FMath::Clamp(FMath::RoundToInt(Value), 0, 4);
    ApplyGraphicsSettings();
}

void UUW_MainMenu::OnFoliageChanged(float Value)
{
    FoliageQuality = FMath::Clamp(FMath::RoundToInt(Value), 0, 4);
    ApplyGraphicsSettings();
}

void UUW_MainMenu::OnShadingChanged(float Value)
{
    ShadingQuality = FMath::Clamp(FMath::RoundToInt(Value), 0, 4);
    ApplyGraphicsSettings();
}