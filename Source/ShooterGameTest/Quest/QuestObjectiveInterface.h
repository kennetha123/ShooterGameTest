#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "QuestObjectiveInterface.generated.h"

class UQuestObjectiveDataAsset;

UINTERFACE(MinimalAPI, Blueprintable)
class UQuestObjectiveInterface : public UInterface
{
    GENERATED_BODY()
};

class IQuestObjectiveInterface
{
    GENERATED_BODY()

public:
    virtual void Initialize(UQuestObjectiveDataAsset* ObjectiveData) = 0;
    virtual void UpdateProgress(AActor* Actor = nullptr) = 0;
    virtual bool IsComplete() const = 0;

    virtual FString GetTitle() const = 0;
    virtual FString GetDescription() const = 0;

};
