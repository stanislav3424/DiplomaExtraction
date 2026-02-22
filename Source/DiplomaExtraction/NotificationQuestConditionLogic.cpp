// Fill out your copyright notice in the Description page of Project Settings.

#include "NotificationQuestConditionLogic.h"
#include "ExfilGameState.h"
#include "MacroLibrary.h"
#include "LogicLibrary.h"
#include "Row.h"
#include "QuestLogic.h"
#include "Components/BoxComponent.h"
#include "NotificationWidgetComponent.h"
#include "EnumLibrary.h"
#include "PresenceDetectorSceneComponent.h"

void UNotificationQuestConditionLogic::OwnerLogicChange(ULogicBase* OldOwnerLogic, ULogicBase* NewOwnerLogic)
{
    Super::OwnerLogicChange(OldOwnerLogic, NewOwnerLogic);

    if (OldOwnerLogic)
        OldOwnerLogic->OnRepresentationActorChanged.RemoveAll(this);

    if (NewOwnerLogic)
        NewOwnerLogic->OnRepresentationActorChanged.AddUniqueDynamic(
            this, &UNotificationQuestConditionLogic::OwnerRepresentationActorChanged);
}

bool UNotificationQuestConditionLogic::ApplyQuestItem(ULogicBase* QuestItem)
{
    auto Result = Super::ApplyQuestItem(QuestItem);

    if (Result)
    {
        auto GameState = AExfilGameState::Get(GetWorld());
        CHECK_VAR_RETURN_VALUE(GameState, Result);

        GameState->QuestCompleted(QuestItem);
    }

    return Result;
}


void UNotificationQuestConditionLogic::OwnerRepresentationActorChanged(AActor* NewRepresentationActor)
{
    CHECK_VAR_RETURN(NewRepresentationActor);

    if (PresenceDetector)
    {
        PresenceDetector->OnNewActor.RemoveAll(this);
        PresenceDetector = nullptr;
    }

    PresenceDetector = NewRepresentationActor->FindComponentByTag<UPresenceDetectorSceneComponent>(PresenceTag);
    CHECK_VAR_RETURN(PresenceDetector);

    PresenceDetector->OnNewActor.AddUniqueDynamic(this, &UNotificationQuestConditionLogic::OnPlayerEntered);
}

void UNotificationQuestConditionLogic::OnPlayerEntered(AActor* Player)
{
    if (!IsValid(Player))
        return;

    if (IsAreAllQuestsCompleted())
        return;

    auto Logic = ULogicLibrary::GetLogic(Player);
    if (!Logic)
        return;

    TArray<UQuestLogic*> Quests;
    Logic->GetLogicComponents<UQuestLogic>(Quests, true);

    for (auto Quest : Quests)
        ApplyQuestItem(Quest);

    if (IsAreAllQuestsCompleted())
        return;

    Notification(Player);
}

void UNotificationQuestConditionLogic::Notification(AActor* Player)
{
    if (!IsValid(Player))
        return;

    auto Notification = Player->FindComponentByClass<UNotificationWidgetComponent>();
    CHECK_VAR_RETURN(Notification);

    FString ItemsString;
    for (auto const& Quest : QuestsStatus)
    {
        if (Quest.Value)
            break;
        FName EnumName = UEnumLibrary::EnumToName(Quest.Key);
        ItemsString += EnumName.ToString() + TEXT(", ");
    }

    ItemsString.RemoveFromEnd(TEXT(", "));
    Notification->AddNotification(FText::FromString(FString::Printf(TEXT("Need an item: %s"), *ItemsString)), 2.f);
}
