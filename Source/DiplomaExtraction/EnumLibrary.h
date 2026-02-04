// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EnumLibrary.generated.h"

UCLASS()
class DIPLOMAEXTRACTION_API UEnumLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    template <typename TypeEnum> static FName EnumToName(TypeEnum Value)
    {
        if (UEnum* Enum = StaticEnum<TypeEnum>())
        {
            FString String = Enum->GetNameStringByValue(static_cast<int64>(Value));
            return FName(*String);
        }
        return NAME_None;
    }
    template <typename TypeEnum> static TypeEnum NameToEnum(FName Name)
    {
        if (UEnum* Enum = StaticEnum<TypeEnum>())
        {
            int64 Value = Enum->GetValueByNameString(Name.ToString());
            if (Value != INDEX_NONE)
                return static_cast<TypeEnum>(Value);
        }
        return static_cast<TypeEnum>(0);
    }
};
