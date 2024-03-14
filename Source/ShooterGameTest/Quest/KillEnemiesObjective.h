#pragma once

#include "CoreMinimal.h"
#include "QuestObjectiveInterface.h"
#include "KillEnemiesObjective.generated.h"

class AEnemyActorComponent;
class UQuestObjectiveDataAsset;

UCLASS(Blueprintable)
class SHOOTERGAMETEST_API UKillEnemiesObjective : public UObject, public IQuestObjectiveInterface
{
    GENERATED_BODY()

public:
    DECLARE_MULTICAST_DELEGATE_OneParam(FOnEnemyKilled, AEnemyActorComponent*);
    FOnEnemyKilled OnEnemyKilled;

    void Initialize(UQuestObjectiveDataAsset* ObjectiveData);
    virtual void UpdateProgress(AActor* Actor = nullptr) override;
    virtual bool IsComplete() const override;

    virtual FString GetTitle() const override;
    virtual FString GetDescription() const override;

private:
    UQuestObjectiveDataAsset* ObjectiveDataAsset;

    int CurrentKillCount = 0;
};

