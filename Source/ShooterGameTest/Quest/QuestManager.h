// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestObjective.h"
#include "QuestManager.generated.h"

UCLASS()
class SHOOTERGAMETEST_API AQuestManager : public AActor
{
	GENERATED_BODY()
	
public:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere)
    UQuestDataAsset* Quests;

    UFUNCTION()
    void OnEnemyKilled(AEnemyActorComponent* Enemy);
    UFUNCTION()
    void OnLocationReached(ADestinationObjective* Destination);
};
