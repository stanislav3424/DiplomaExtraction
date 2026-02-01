// Fill out your copyright notice in the Description page of Project Settings.

#include "IconRendering.h"
#include "Components/SceneCaptureComponent2D.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/TextureRenderTarget2D.h"
#include "LogicBase.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "SpawnLibrary.h"
#include "MacroLibrary.h"
#include "ExfilGameMode.h"

AIconRendering::AIconRendering()
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.TickInterval = 0.2f;

    auto Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SetRootComponent(Root);

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(Root);
    SpringArm->bDoCollisionTest = false;

    SceneCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("SceneCapture"));
    SceneCapture->SetupAttachment(SpringArm);
    SceneCapture->bCaptureEveryFrame = false;
    SceneCapture->bCaptureOnMovement = false;
}

void AIconRendering::BeginPlay()
{
    Super::BeginPlay();
}

void AIconRendering::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (WarmupCapture(DeltaSeconds))
        return;

    TPair<FDataTableRowHandle, UTextureRenderTarget2D*> Pair;
    if (QueueRender.Dequeue(Pair))
    {
        if (!SceneCapture)
            return;

        const FDataTableRowHandle& RowHandle    = Pair.Key;
        UTextureRenderTarget2D*    RenderTarget = Pair.Value;
        TSubclassOf<AActor>        Class;

        SceneCapture->TextureTarget = RenderTarget;

        auto World = GetWorld();
        if (!World)
            return;

        auto Row = RowHandle.GetRow<FLogicBaseRow>(FILE_FUNC);
        if (!Row)
            return;

        Class = Row->RepresentationActorClass;
        if (!Class)
            return;

        FActorSpawnParameters ActorSpawnParameters;
        ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        auto Actor = World->SpawnActor<AActor>(Class, GetActorTransform(), ActorSpawnParameters);
        if (!Actor)
            return;
        SettingCamera(Actor);

        SceneCapture->CaptureScene();
        Actor->Destroy();

        if (!RenderTarget)
            return;
        if (auto Found = CacheTextures.Find(RowHandle.RowName))
            Found->Value = true;

        if (auto TargetWaitingMIDs = WaitingMIDs.Find(RenderTarget))
        {
            for (auto WaitingMID : *TargetWaitingMIDs)
                if (WaitingMID)
                    WaitingMID->SetScalarParameterValue(MIDTextureReadyParameterName, 1.f);

            WaitingMIDs.Remove(RenderTarget);
        }
    }
}

bool AIconRendering::WarmupCapture(float DeltaSeconds)
{
    if (WarmupTime > 0.f || IsAsyncLoading())
    {
        if (!SceneCapture->TextureTarget)
            SceneCapture->TextureTarget = GetNewRenderTarget();
        SceneCapture->bCaptureEveryFrame = true;
        WarmupTime -= DeltaSeconds;
        return true;
    }

    SceneCapture->bCaptureEveryFrame = false;

    return false;
}

UTextureRenderTarget2D* AIconRendering::GetNewRenderTarget()
{
    auto NewRenderTarget = NewObject<UTextureRenderTarget2D>(this);
    if (!NewRenderTarget)
        return nullptr;
    const int32 RTSize = 256;
    NewRenderTarget->InitAutoFormat(RTSize, RTSize);
    NewRenderTarget->ClearColor = FLinearColor::Green;
    return NewRenderTarget;
}

void AIconRendering::SettingCamera(AActor* Actor)
{
    if (!Actor || !SceneCapture)
        return;

    SceneCapture->ShowOnlyActors.Empty();
    SceneCapture->ShowOnlyComponents.Empty();
    SceneCapture->ShowOnlyActorComponents(Actor, true);
    SetLightingChannels(Actor);

    FVector Origin;
    FVector Extent;
    Actor->GetActorBounds(true, Origin, Extent);
    float RequiredOrthoWidth     = FMath::Max(Extent.X, Extent.Y, Extent.Z) * 2.2f;
    SceneCapture->ProjectionType = ECameraProjectionMode::Orthographic;
    SceneCapture->OrthoWidth     = RequiredOrthoWidth;

    FVector Location = this->GetActorLocation();
    FVector Delta    = Location - Origin;
    Actor->SetActorLocation(Location + Delta);
}

void AIconRendering::SetLightingChannels(AActor* Actor)
{
    const bool bChannel0 = false;
    const bool bChannel1 = true;
    const bool bChannel2 = false;

    auto Components = Actor->GetComponents().Array();
    for (auto Component : Components)
        if (auto PrimitiveComponent = Cast<UPrimitiveComponent>(Component))
            PrimitiveComponent->SetLightingChannels(bChannel0, bChannel1, bChannel2);
}

void AIconRendering::GetIcon_(ULogicBase* Logic, UMaterialInstanceDynamic* MID)
{
    if (!Logic || !MID)
        return;

    auto& RowHandle = Logic->GetRowHandle();
    if (auto* Found = CacheTextures.Find(RowHandle.RowName))
    {
        auto RenderTarget = (*Found).Key;
        bool bReady       = (*Found).Value;

        if (RenderTarget)
        {
            MID->SetTextureParameterValue(MIDTextureParameterName, RenderTarget);

            if (bReady)
                MID->SetScalarParameterValue(MIDTextureReadyParameterName, 1.f);
            else
                WaitingMIDs.FindOrAdd(RenderTarget).Add(MID);
        }

        return;
    }

    if (auto NewRenderTarget = GetNewRenderTarget())
    {
        CacheTextures.Add(RowHandle.RowName, TPair<UTextureRenderTarget2D*, bool>(NewRenderTarget, false));
        QueueRender.Enqueue(TPair<FDataTableRowHandle, UTextureRenderTarget2D*>(RowHandle, NewRenderTarget));

        MID->SetTextureParameterValue(MIDTextureParameterName, NewRenderTarget);
        WaitingMIDs.FindOrAdd(NewRenderTarget).Add(MID);
    }
}

void AIconRendering::GetIcon(ULogicBase* Logic, UMaterialInstanceDynamic* MID)
{
    if (!Logic || !MID)
        return;

    auto World = Logic->GetWorld();
    if (!World)
        return;

    auto GM = Cast<AExfilGameMode>(World->GetAuthGameMode());
    if (!GM)
        return;

    auto IconRendering = GM->GetIconRenderer();
    if (!IconRendering)
        return;

    IconRendering->GetIcon_(Logic, MID);
}
