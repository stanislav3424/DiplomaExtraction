// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestConditionLogic.h"
#include "MacroLibrary.h"
#include "LogicLibrary.h"
#include "Row.h"
#include "QuestLogic.h"
#include "Components/BoxComponent.h"
#include "NotificationWidgetComponent.h"
#include "EnumLibrary.h"

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
        UE_LOG(InitGameLogic, Error, FILE_FUNC TEXT("Zero quests initialized"))
}

void UQuestConditionLogic::OwnerLogicChange(ULogicBase* NewOwnerLogic)
{
    Super::OwnerLogicChange(NewOwnerLogic);

    if (!NewOwnerLogic)
        return;

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

void UQuestConditionLogic::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!IsValid(OtherActor))
        return;

    if (IsAreAllQuestsCompleted())
        return;

    auto PC = OtherActor->GetInstigatorController<APlayerController>();
    if (!PC)
        return;

    auto Logic = ULogicLibrary::GetLogic(OtherActor);
    if (!Logic)
        return;

    TArray<UQuestLogic*> Quests;
    Logic->GetLogicComponents<UQuestLogic>(Quests, true);

    for (auto Quest : Quests)
    {
        ApplyQuestItem(Quest->GetOwnerLogic());
    }

    if (IsAreAllQuestsCompleted())
        return;

    auto Notification = OtherActor->FindComponentByClass<UNotificationWidgetComponent>();
    CHECK_FIELD_RETURN(Notification);

    FString ItemsString;
    for (auto const& Quest : QuestsStatus)
    {
        if (Quest.Value)
            break;
        FName EnumName = UEnumLibrary::EnumToName(Quest.Key);
        ItemsString += EnumName.ToString() + TEXT(", ");
    }

    ItemsString.RemoveFromEnd(TEXT(", "));
    Notification->Notification(FText::FromString(FString::Printf(TEXT("Need an item: %s"), *ItemsString)), 2.f);
}

void UQuestConditionLogic::OnBoxEndOverlap(
    UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void UQuestConditionLogic::OwnerRepresentationActorChanged(AActor* NewRepresentationActor)
{
    CHECK_FIELD_RETURN(NewRepresentationActor);

    if (CollisionBox)
        return;

    CollisionBox = NewRepresentationActor->FindComponentByTag<UBoxComponent>(CollisionBoxTag);
    CHECK_FIELD_RETURN(CollisionBox);

    CollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &UQuestConditionLogic::OnBoxBeginOverlap);
    CollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &UQuestConditionLogic::OnBoxEndOverlap);
}
