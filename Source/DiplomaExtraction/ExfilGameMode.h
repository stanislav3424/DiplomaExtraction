// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ExfilGameMode.generated.h"

UENUM(BlueprintType)
enum class EStatusGame : uint8
{
    NotStarted UMETA(DisplayName = "NotStarted"),
    Started    UMETA(DisplayName = "Started"),
    Over       UMETA(DisplayName = "Over"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGamePausedChanged, bool, bIsPaused);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatusGameChanged, EStatusGame const&, NewStatusGame);

class AIconRendering;

UCLASS(Abstract, Blueprintable)
class DIPLOMAEXTRACTION_API AExfilGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    static AExfilGameMode* Get(UObject* WorldContextObject);

protected:
    virtual void BeginPlay() override;
    void         SpawnIconRendering();
    void         LevelStartSetting();

    // IconRenderer
protected:
    UPROPERTY(Transient)
    AIconRendering* IconRenderer;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Classes)
    TSubclassOf<AIconRendering> IconRendererClass;

public:
    AIconRendering*        GetIconRenderer() const { return IconRenderer; }
    static AIconRendering* GetIconRenderer(UObject* WorldContextObject);

    // Status Game
public:
    void                 TogglePause();
    void                 SetPauseGame(bool bPause);
    FOnGamePausedChanged OnGamePausedChanged;
    void                 BroadcastGamePausedChanged() const;

    FOnStatusGameChanged OnStatusGameChanged;
    void                 BroadcastStatusGameChanged() const;

    UFUNCTION(BlueprintCallable)
    void StartGame();
    UFUNCTION(BlueprintCallable)
    void EndGame();
    UFUNCTION(BlueprintCallable)
    void ReloadGame();
    UFUNCTION(BlueprintCallable)
    void ReloadGameAndStartGame();

private:
    void SetStatusGame(EStatusGame const& NewStatusGame);
    EStatusGame StatusGame = EStatusGame::NotStarted;
    bool bIsPaused = false;
};
