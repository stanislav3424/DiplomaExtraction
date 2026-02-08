// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestConditionLogic.h"
#include "MacroLibrary.h"
#include "Row.h"
#include "QuestLogic.h"

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

        QuestsStatus.Add(TPair<ETypeQuest, bool>(Quest, false));
    }

    CheckQuestsCompleted();
    if (IsAreAllQuestsCompleted())
        UE_LOG(InitGameLogic, Error, FILE_FUNC TEXT("Zero quests initialized"))
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
    QuestsStatus.Add(TPair<ETypeQuest, bool>(TypeQuest, true));

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
