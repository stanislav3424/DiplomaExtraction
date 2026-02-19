// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "UW_Notification.generated.h"

class UTextBlock;
class UListView;

UCLASS(NotBlueprintable)
class DIPLOMAEXTRACTION_API UNotificationItem : public UObject
{
    GENERATED_BODY()

public:
    void RemoveItem();
    void SetOwnerNotification(UUW_Notification* NewOwnerNotification) { OwnerNotification = NewOwnerNotification; };

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Text;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Lifetime = 0.f;

private:
    UPROPERTY(Transient)
    UUW_Notification* OwnerNotification;
};

UCLASS(Abstract, Blueprintable)
class DIPLOMAEXTRACTION_API UUW_Notification : public UUserWidget
{
    GENERATED_BODY()

public:
    void AddNotification(FText Text, float Duration = 3.f);
    void RemoveItem(UObject* Item);

private:
    UPROPERTY(meta = (BindWidget))
    UListView* ListView;
};

UCLASS(Abstract, Blueprintable)
class DIPLOMAEXTRACTION_API UUW_NotificationEntry : public UUserWidget, public IUserObjectListEntry
{
    GENERATED_BODY()

protected:
    virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

private:
    UPROPERTY(meta = (BindWidget)) 
    UTextBlock* TextBlock;
};