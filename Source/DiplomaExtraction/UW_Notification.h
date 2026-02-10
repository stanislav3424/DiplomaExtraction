// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UW_Base.h"
#include "UW_Notification.generated.h"

class UTextBlock;

UCLASS(Abstract, Blueprintable)
class DIPLOMAEXTRACTION_API UUW_Notification : public UUW_Base
{
    GENERATED_BODY()

public:
    void SetText(FText Text);

private:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* TextWidget;
};
