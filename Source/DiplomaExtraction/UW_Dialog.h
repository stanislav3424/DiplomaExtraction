// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UW_Base.h"
#include "UW_Dialog.generated.h"

UCLASS(Abstract, NotBlueprintable)
class DIPLOMAEXTRACTION_API UUW_Dialog : public UUW_Base
{
    GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

    UPROPERTY(meta = (BindWidgetAnimOptional))
    UWidgetAnimation* DialogAnimation;

public:
    void ToggleDialog();
    void OpenDialog();
    void CloseDialog();
    bool IsOpen() const { return bIsOpen; }

private:
    bool         bIsOpen = true;
    FTimerHandle FinishTimerHandle;

protected:
    virtual void StartOpen() {};
    virtual void StartClose() {};
    virtual void FinishOpen();
    virtual void FinishClose();
};
