// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MacroLibrary.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(InitGameLogic, Log, All);

// UE_LOG(InitGameLogic, Error, TEXT(""))

#define FILE_FUNC TEXT(__FILE__) TEXT(":") TEXT(__FUNCTION__)

#define FILE_FUNC_LINE TEXT(__FILE__) TEXT(":") TEXT(__FUNCTION__) TEXT(":") TEXT(STRINGIFY(__LINE__))

#define CHECK_FIELD(FieldName)                                                                                         \
    if (!(FieldName))                                                                                                  \
    {                                                                                                                  \
        UE_LOG(                                                                                                        \
            InitGameLogic, Error, TEXT("%s LINE %d Field '%s' is not set!"), *GetName(), __LINE__, TEXT(#FieldName));  \
    }

#define CHECK_FIELD_RETURN(FieldName)                                                                                  \
    if (!(FieldName))                                                                                                  \
    {                                                                                                                  \
        UE_LOG(                                                                                                        \
            InitGameLogic, Error, TEXT("%s LINE %d Field '%s' is not set!"), *GetName(), __LINE__, TEXT(#FieldName));  \
        return;                                                                                                        \
    }

#define CHECK_FIELD_RETURN_VALUE(FieldName, ReturnValue)                                                               \
    if (!(FieldName))                                                                                                  \
    {                                                                                                                  \
        UE_LOG(                                                                                                        \
            InitGameLogic, Error, TEXT("%s LINE %d Field '%s' is not set!"), *GetName(), __LINE__, TEXT(#FieldName));  \
        return ReturnValue;                                                                                            \
    }

UCLASS()
class DIPLOMAEXTRACTION_API UMacroLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};
