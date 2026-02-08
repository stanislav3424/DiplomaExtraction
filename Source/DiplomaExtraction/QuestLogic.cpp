// Fill out your copyright notice in the Description page of Project Settings.

#include "QuestLogic.h"
#include "MacroLibrary.h"
#include "Row.h"

void UQuestLogic::InitializeRowHandler(FDataTableRowHandle const& InitRowHandle)
{
    Super::InitializeRowHandler(InitRowHandle);

    auto Row = InitRowHandle.GetRow<FQuestRow>(FILE_FUNC);
    if (!Row)
        return;

    TypeQuest = Row->TypeQuest;

    if (TypeQuest == ETypeQuest::None)
        UE_LOG(InitGameLogic, Error, FILE_FUNC TEXT("TypeQuest = ETypeQuest::None"))
}
