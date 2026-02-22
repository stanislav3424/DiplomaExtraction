// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ListenQuestConditionLogic.h"
#include "NotificationQuestConditionLogic.generated.h"

UCLASS(NotBlueprintable)
class DIPLOMAEXTRACTION_API UNotificationQuestConditionLogic : public UListenQuestConditionLogic
{
    GENERATED_BODY()

protected:
    virtual void OwnerLogicChange(ULogicBase* OldOwnerLogic, ULogicBase* NewOwnerLogic) override;

public:
    virtual bool ApplyQuestItem(ULogicBase* QuestItem) override;

private:
    FName PresenceTag = TEXT("Player");

    UFUNCTION()
    void OwnerRepresentationActorChanged(AActor* NewRepresentationActor);

    UPROPERTY(Transient)
    UPresenceDetectorSceneComponent* PresenceDetector;

    UFUNCTION()
    void OnPlayerEntered(AActor* Player);

    void Notification(AActor* Player);
};
