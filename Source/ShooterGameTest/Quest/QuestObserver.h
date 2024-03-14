// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QuestObserver.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UQuestObserver : public UInterface
{
	GENERATED_BODY()
};

class SHOOTERGAMETEST_API IQuestObserver
{
	GENERATED_BODY()

public:
	virtual void OnEnemyKilled(AActor* Enemy) = 0;
};
