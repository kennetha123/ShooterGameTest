// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestObjective.h"
#include "QuestObserver.h"
#include "QuestManager.generated.h"

UCLASS()
class SHOOTERGAMETEST_API AQuestManager : public AActor, public IQuestObserver
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditAnywhere)
    UQuestDataAsset* Quests;

    virtual void OnEnemyKilled(AActor* Enemy) override;
};
