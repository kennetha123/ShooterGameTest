// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataAsset.h"
#include "QuestObjective.generated.h"

UENUM(BlueprintType)
enum class EObjectiveType : uint8
{
    KillEnemies UMETA(DisplayName = "Kill Enemies"),
    ReachLocation UMETA(DisplayName = "Reach Location")
};

class ADestinationObjective;

UCLASS(BlueprintType)
class SHOOTERGAMETEST_API UQuestObjectiveDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
    FString Title;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
    EObjectiveType ObjectiveType;

    UFUNCTION(BlueprintCallable, Category = "Objective")
    bool IsObjectiveComplete() const;

    // For "Kill Enemies" objective
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective", meta = (EditCondition = "ObjectiveType == EObjectiveType::KillEnemies"))
    int32 NumberOfEnemiesToKill;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Objective")
    int32 CurrentKillCount;

    UFUNCTION(BlueprintCallable, Category = "Objective")
    void IncrementKillCount();

    // For "Reach Location" objective
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective", meta = (EditCondition = "ObjectiveType == EObjectiveType::ReachLocation"))
    FName DestinationTag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective", meta = (EditCondition = "ObjectiveType == EObjectiveType::ReachLocation"))
    float LocationRadius;
};

UCLASS(BlueprintType)
class SHOOTERGAMETEST_API UQuestDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    TArray<UQuestObjectiveDataAsset*> Objectives;
};