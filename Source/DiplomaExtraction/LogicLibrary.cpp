// Fill out your copyright notice in the Description page of Project Settings.

#include "LogicLibrary.h"
#include "LogicInterface.h"
#include "LogicBase.h"

ULogicBase* ULogicLibrary::GetLogic(TScriptInterface<ILogicInterface> TargetObject)
{
	if (TargetObject)
		return TargetObject->Execute_GetLogic(TargetObject.GetObject());
	return nullptr;
}

void ULogicLibrary::SetLogic(TScriptInterface<ILogicInterface> TargetObject, ULogicBase* NewLogic)
{
	if (TargetObject)
		TargetObject->Execute_SetLogic(TargetObject.GetObject(), NewLogic);
}

void ULogicLibrary::AddLogicComponent(TScriptInterface<ILogicInterface> TargetObject, ULogicBase* Component)
{
	ULogicBase* Logic = GetLogic(TargetObject);
	if (Logic)
		Logic->AddLogicComponent(Component);
}

void ULogicLibrary::RemoveLogicComponent(TScriptInterface<ILogicInterface> TargetObject, ULogicBase* Component)
{
	ULogicBase* Logic = GetLogic(TargetObject);
	if (Logic)
		Logic->RemoveLogicComponent(Component);
}
