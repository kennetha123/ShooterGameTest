// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameTestGameInstance.h"

void UShooterGameTestGameInstance::Init()
{
    Super::Init();

    UWorld* World = GetWorld();
    if (World && QuestManagerClass != nullptr)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        QuestManagerInstance = World->SpawnActor<AQuestManager>(QuestManagerClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
    }
}