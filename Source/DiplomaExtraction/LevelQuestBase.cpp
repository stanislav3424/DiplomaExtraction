// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelQuestBase.h"

// Sets default values
ALevelQuestBase::ALevelQuestBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelQuestBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALevelQuestBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

