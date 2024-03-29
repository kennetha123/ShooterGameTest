#pragma once

#include "CoreMinimal.h"
#include "QuestObjectiveInterface.h"
#include "DestinationObjective.generated.h"


class UQuestObjectiveDataAsset;
class ADestinationActor;

UCLASS(Blueprintable)
class SHOOTERGAMETEST_API UDestinationObjective : public UObject, public IQuestObjectiveInterface
{
    GENERATED_BODY()

public:
    DECLARE_MULTICAST_DELEGATE_OneParam(FOnLocationReached, ADestinationActor*);
    FOnLocationReached OnLocationReached;

    void Initialize(UQuestObjectiveDataAsset* ObjectiveData);
    virtual void UpdateProgress(AActor* Actor = nullptr) override;
    virtual bool IsComplete() const override;

    virtual FString GetTitle() const override;
    virtual FString GetDescription() const override;

private:
    UQuestObjectiveDataAsset* ObjectiveDataAsset;

    bool bIsComplete;
};

