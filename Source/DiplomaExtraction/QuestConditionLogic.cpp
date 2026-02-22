// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestConditionLogic.h"
#include "MacroLibrary.h"
#include "LogicLibrary.h"
#include "Row.h"
#include "QuestLogic.h"
#include "Components/BoxComponent.h"
#include "NotificationWidgetComponent.h"
#include "EnumLibrary.h"
#include "PresenceDetectorSceneComponent.h"

void UQuestConditionLogic::InitializeRowHandler(FDataTableRowHandle const& InitRowHandle)
{
    Super::InitializeRowHandler(InitRowHandle);

    auto Row = InitRowHandle.GetRow<FQuestConditionRow>(FILE_FUNC);
    if (!Row)
        return;

    QuestsStatus.Reserve(Row->Quests.Num());

    for (auto Quest : Row->Quests)
    {
        if (Quest == ETypeQuest::None)
        {
            UE_LOG(InitGameLogic, Error, FILE_FUNC TEXT("Quest = ETypeQuest::None"))
            break;
        }

        QuestsStatus.Add(Quest, false);
    }

    CheckQuestsCompleted();
    if (IsAreAllQuestsCompleted())
        UE_LOG(InitGameLogic, Error, FILE_FUNC TEXT("Zero quests initialized"));

   PresenceTag = UEnumLibrary::EnumToName(ETypeTracking::Player);
}

void UQuestConditionLogic::OwnerLogicChange(ULogicBase* OldOwnerLogic, ULogicBase* NewOwnerLogic)
{
    Super::OwnerLogicChange(OldOwnerLogic, NewOwnerLogic);

    if (OldOwnerLogic)
        OldOwnerLogic->OnRepresentationActorChanged.RemoveAll(this);

    if (NewOwnerLogic)
        NewOwnerLogic->OnRepresentationActorChanged.AddUniqueDynamic(
            this, &UQuestConditionLogic::OwnerRepresentationActorChanged);
}

bool UQuestConditionLogic::ApplyQuestItem(ULogicBase* QuestItem)
{
    if (AreAllQuestsCompleted)
        return false;

    if (!CheckQuestItem(QuestItem))
        return false;

    auto QuestLogic = QuestItem->GetLogicComponent<UQuestLogic>();
    if (!QuestLogic)
        return false;

    auto TypeQuest = QuestLogic->GetTypeQuest();
    QuestsStatus.Add(TypeQuest, true);

    CheckQuestsCompleted();

    return true;
}

bool UQuestConditionLogic::CheckQuestItem(ULogicBase* QuestItem)
{
    if (!QuestItem)
        return false;
    auto QuestLogic = QuestItem->GetLogicComponent<UQuestLogic>();
    if (!QuestLogic)
        return false;
    auto TypeQuest = QuestLogic->GetTypeQuest();
    for (auto QuestStatus : QuestsStatus)
        if (QuestStatus.Key == TypeQuest)
            return true;
    return false;
}

void UQuestConditionLogic::CheckQuestsCompleted()
{
    for (auto QuestStatus : QuestsStatus)
        if (QuestStatus.Value == false)
            return;
    
    AreAllQuestsCompleted = true;
    OnAllQuestsCompleted.Broadcast();
}

void UQuestConditionLogic::OwnerRepresentationActorChanged(AActor* NewRepresentationActor)
{
    CHECK_VAR_RETURN(NewRepresentationActor);

    if (PresenceDetector)
    {
        PresenceDetector->OnNewActor.RemoveAll(this);
        PresenceDetector = nullptr;
    }

    PresenceDetector = NewRepresentationActor->FindComponentByTag<UPresenceDetectorSceneComponent>(PresenceTag);
    CHECK_VAR_RETURN(PresenceDetector);

    PresenceDetector->OnNewActor.AddUniqueDynamic(this, &UQuestConditionLogic::OnPlayerEntered);
}

void UQuestConditionLogic::OnPlayerEntered(AActor* Player)
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
        ApplyQuestItem(Quest->GetOwnerLogic());

    if (IsAreAllQuestsCompleted())
        return;

    Notification(Player);
}

void UQuestConditionLogic::Notification(AActor* Player)
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
