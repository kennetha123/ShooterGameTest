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

    // For "Kill Enemies" objective
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective", meta = (EditCondition = "ObjectiveType == EObjectiveType::KillEnemies"))
    int32 NumberOfEnemiesToKill;

    // For "Reach Location" objective
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective", meta = (EditCondition = "ObjectiveType == EObjectiveType::ReachLocation"))
    TArray<FVector> Locations;

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