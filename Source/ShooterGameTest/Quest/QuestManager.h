#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestObjective.h"
#include "QuestObjectiveInterface.h"
#include "QuestManager.generated.h"

UCLASS()
class SHOOTERGAMETEST_API AQuestManager : public AActor
{
	GENERATED_BODY()
	
public:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere)
    UQuestDataAsset* QuestsData;
    TArray<UObject*> QuestsObjective;

    UFUNCTION()
    void OnEnemyKilled(AEnemyActorComponent* Enemy);
    UFUNCTION()
    void OnLocationReached(ADestinationActor* Destination);
};
