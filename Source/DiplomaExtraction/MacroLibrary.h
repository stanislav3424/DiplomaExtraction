// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MacroLibrary.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(InitGameLogic, Log, All);

// UE_LOG(InitGameLogic, Error, TEXT(""))

#define FILE_FUNC TEXT(__FILE__) TEXT(":") TEXT(__FUNCTION__)

#define FILE_FUNC_LINE TEXT(__FILE__) TEXT(":") TEXT(__FUNCTION__) TEXT(":") TEXT(__LINE__)

#define CHECK_VAR(VarName)                                                                                             \
    if (!(VarName))                                                                                                    \
    {                                                                                                                  \
        UE_LOG(InitGameLogic, Error, TEXT("%s LINE %d: Expected a valid value for variable '%s'"), *GetName(),         \
            __LINE__, TEXT(#VarName));                                                                                 \
    }

#define CHECK_VAR_RETURN(VarName)                                                                                      \
    if (!(VarName))                                                                                                    \
    {                                                                                                                  \
        UE_LOG(InitGameLogic, Error, TEXT("%s LINE %d: Expected a valid value for variable '%s'"), *GetName(),         \
            __LINE__, TEXT(#VarName));                                                                                 \
        return;                                                                                                        \
    }

#define CHECK_VAR_RETURN_VALUE(VarName, ReturnValue)                                                                   \
    if (!(VarName))                                                                                                    \
    {                                                                                                                  \
        UE_LOG(InitGameLogic, Error, TEXT("%s LINE %d: Expected a valid value for variable '%s'"), *GetName(),         \
            __LINE__, TEXT(#VarName));                                                                                 \
        return ReturnValue;                                                                                            \
    }

#define HIDE_COLLISION(Actor) UMacroLibrary::HideCollisionComponentsForShipping(Actor);

UCLASS()
class DIPLOMAEXTRACTION_API UMacroLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Utils")
    static void HideCollisionComponentsForShipping(AActor* Actor)
    {
#if UE_BUILD_SHIPPING

        if (!Actor)
            return;
        TArray<UPrimitiveComponent*> PrimitiveComponents;
        Actor->GetComponents<UPrimitiveComponent>(PrimitiveComponents);
        for (auto PrimitiveComponent : PrimitiveComponents)
        {
            if (!PrimitiveComponent)
                continue;
            PrimitiveComponent->SetHiddenInGame(true, true);
        }

#endif
    }
};
