// Fill out your copyright notice in the Description page of Project Settings.

#include "UW_Base.h"
#include "Blueprint/WidgetTree.h"
#include "LogicLibrary.h"

ULogicBase* UUW_Base::GetLogic_Implementation()
{
    return Logic;
}

void UUW_Base::SetLogic_Implementation(ULogicBase* NewLogic)
{
    LogicChanged(Logic, NewLogic);
    if (bIsAutoInitializeChildLogic)
        InitializeChildLogic(NewLogic);
}

void UUW_Base::LogicChanged(ULogicBase* OldLogic, ULogicBase* NewLogic)
{
    Logic = NewLogic;
}

void UUW_Base::InitializeChildLogic(ULogicBase* NewLogic)
{
    if (!WidgetTree)
        return;

    TArray<UWidget*> Childrens;
    WidgetTree->GetChildWidgets(this->GetRootWidget(), Childrens);
    for (auto Children : Childrens)
        ULogicLibrary::SetLogic(Children, NewLogic);
}
