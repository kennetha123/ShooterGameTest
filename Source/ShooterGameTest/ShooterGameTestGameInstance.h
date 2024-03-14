// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Quest/QuestManager.h"
#include "ShooterGameTestGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAMETEST_API UShooterGameTestGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

    virtual void Init() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Quest")
    TSubclassOf<AQuestManager> QuestManagerClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quest")
    AQuestManager* QuestManagerInstance;

    AQuestManager* GetQuestManager() const { return QuestManagerInstance; }
};
