// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LogicInterface.h"
#include "LogicLibrary.generated.h"

class ILogicInterface;
class ULogicBase;

UCLASS()
class DIPLOMAEXTRACTION_API ULogicLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    static ULogicBase* GetLogic(TScriptInterface<ILogicInterface> TargetObject);
    static void        SetLogic(TScriptInterface<ILogicInterface> TargetObject, ULogicBase* NewLogic);

    template <typename TypeLogic = ULogicBase> static TypeLogic* GetLogic(TScriptInterface<ILogicInterface> TargetObject)
    {
        return Cast<TypeLogic>(GetLogic(TargetObject));
    }

    static void AddLogicComponent(TScriptInterface<ILogicInterface> TargetObject, ULogicBase* Component);
    static void RemoveLogicComponent(TScriptInterface<ILogicInterface> TargetObject, ULogicBase* Component);

};
