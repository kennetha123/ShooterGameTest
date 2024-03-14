#include "KillEnemiesObjective.h"
#include "QuestObjective.h"
#include <Kismet/GameplayStatics.h>
#include <ShooterGameTest/EnemyActorComponent.h>

void UKillEnemiesObjective::Initialize(UQuestObjectiveDataAsset* ObjectiveData)
{
    CurrentKillCount = 0;

    ObjectiveDataAsset = ObjectiveData;

    TArray<AActor*> FoundEnemies;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyActorComponent::StaticClass(), FoundEnemies);

    for (AActor* Actor : FoundEnemies)
    {
        AEnemyActorComponent* EnemyActor = Cast<AEnemyActorComponent>(Actor);
        if (EnemyActor)
        {
            EnemyActor->OnEnemyKilled = OnEnemyKilled;
        }
    }
}

void UKillEnemiesObjective::UpdateProgress(AActor* Actor)
{
    CurrentKillCount++;
}

bool UKillEnemiesObjective::IsComplete() const
{
    return CurrentKillCount >= ObjectiveDataAsset->NumberOfEnemiesToKill;
}

FString UKillEnemiesObjective::GetTitle() const
{
    return ObjectiveDataAsset->Title;
}

FString UKillEnemiesObjective::GetDescription() const
{
    return ObjectiveDataAsset->Description;
}
