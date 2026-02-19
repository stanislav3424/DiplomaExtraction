// Fill out your copyright notice in the Description page of Project Settings.

#include "UW_Notification.h"
#include "Components/TextBlock.h"
#include "Components/ListView.h"
#include "MacroLibrary.h"

void UNotificationItem::RemoveItem()
{
    if (OwnerNotification)
        OwnerNotification->RemoveItem(this);
}

void UUW_Notification::AddNotification(FText Text, float Duration)
{
    if (!ListView)
        return;

    auto NotificationItem = NewObject<UNotificationItem>(GetWorld());
    if (!NotificationItem)
        return;

    Duration = FMath::Max(Duration, 1.f);

    NotificationItem->Text     = Text;
    NotificationItem->Lifetime = Duration;
    NotificationItem->SetOwnerNotification(this);

    ListView->AddItem(NotificationItem);

}

void UUW_Notification::RemoveItem(UObject* Item)
{
    ListView->RemoveItem(Item);
}

void UUW_NotificationEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
    auto NotificationItem = Cast<UNotificationItem>(ListItemObject);
    CHECK_VAR_RETURN(NotificationItem)

    if (TextBlock)
        TextBlock->SetText(NotificationItem->Text);

    auto World = GetWorld();
    if (!World)
        return;

    FTimerHandle TimerHandle;
    World->GetTimerManager().SetTimer(
        TimerHandle, [NotificationItem]() { NotificationItem->RemoveItem(); }, NotificationItem->Lifetime, false);
}
