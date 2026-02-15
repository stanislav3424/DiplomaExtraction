// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LogicBase.h"
#include "QuestConditionLogic.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllQuestsCompleted);

enum class ETypeQuest : uint8;
class UBoxComponent;

UCLASS(NotBlueprintable)
class DIPLOMAEXTRACTION_API UQuestConditionLogic : public ULogicBase
{
    GENERATED_BODY()

protected:
    virtual void InitializeRowHandler(FDataTableRowHandle const& InitRowHandle) override;
    virtual void OwnerLogicChange(ULogicBase* OldOwnerLogic, ULogicBase* NewOwnerLogic) override;

public:
    TArray<TPair<ETypeQuest, bool>> GetQuestsStatus() { return QuestsStatus.Array(); };
    bool                            ApplyQuestItem(ULogicBase* QuestItem);
    bool                            CheckQuestItem(ULogicBase* QuestItem);
    bool                            IsAreAllQuestsCompleted() const { return AreAllQuestsCompleted; };

    FOnAllQuestsCompleted OnAllQuestsCompleted;

private:
    void CheckQuestsCompleted();

    TMap<ETypeQuest, bool> QuestsStatus;
    bool                   AreAllQuestsCompleted = false;

    FName CollisionBoxTag = TEXT("QuestCollision");
    FName WidgetInfoTag   = TEXT("WidgetInfo");

    UPROPERTY(Transient)
    UBoxComponent* CollisionBox;

    UFUNCTION()
    void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnBoxEndOverlap(
        UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

    UFUNCTION()
    void OwnerRepresentationActorChanged(AActor* NewRepresentationActor);
};
