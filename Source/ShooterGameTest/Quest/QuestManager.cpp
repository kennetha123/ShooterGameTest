
#include "QuestManager.h"
#include "DestinationObjective.h"
#include <Kismet/GameplayStatics.h>
#include <ShooterGameTest/EnemyActorComponent.h>

void AQuestManager::BeginPlay()
{
    Super::BeginPlay();

    for (auto& Objective : Quests->Objectives)
    {
        if (Objective->ObjectiveType == EObjectiveType::ReachLocation)
        {
            TArray<AActor*> FoundActors;
            UGameplayStatics::GetAllActorsWithTag(GetWorld(), Objective->DestinationTag, FoundActors);
            UE_LOG(LogTemp, Log, TEXT("Found reach location quest."));

            for (auto Actor : FoundActors)
            {
                UE_LOG(LogTemp, Log, TEXT("found."));
                ADestinationObjective* DestinationActor = Cast<ADestinationObjective>(Actor);
                if (DestinationActor)
                {
                    UE_LOG(LogTemp, Log, TEXT("bind."));
                    DestinationActor->OnDestinationReached.AddDynamic(this, &AQuestManager::OnLocationReached);
                }
            }
        }

        if (Objective->ObjectiveType == EObjectiveType::KillEnemies)
        {
            Objective->CurrentKillCount = 0;

            TArray<AActor*> FoundEnemies;
            UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyActorComponent::StaticClass(), FoundEnemies);

            for (AActor* Actor : FoundEnemies)
            {
                AEnemyActorComponent* EnemyActor = Cast<AEnemyActorComponent>(Actor);
                if (EnemyActor)
                {
                    EnemyActor->OnEnemyKilled.AddDynamic(this, &AQuestManager::OnEnemyKilled);
                }
            }
        }
    }
}

void AQuestManager::OnEnemyKilled(AEnemyActorComponent* Enemy)
{
    UE_LOG(LogTemp, Log, TEXT("OnEnemyKilled"));

    for (auto& Objective : Quests->Objectives)
    {
        if (Objective->ObjectiveType == EObjectiveType::KillEnemies)
        {
            Objective->IncrementKillCount();
            UE_LOG(LogTemp, Log, TEXT("Quest : enemy remaining : %d / %d!"), Objective->CurrentKillCount, Objective->NumberOfEnemiesToKill);

            if (Objective->IsObjectiveComplete())
            {
                UE_LOG(LogTemp, Log, TEXT("Quest : %s has been completed!"), *Objective->Title);
            }
        }
    }
}

void AQuestManager::OnLocationReached(ADestinationObjective* Destination)
{
    for (auto& Objective : Quests->Objectives)
    {
        if (Objective->ObjectiveType == EObjectiveType::ReachLocation)
        {
            UE_LOG(LogTemp, Log, TEXT("Quest : %s has been completed!"), *Objective->Title);
        }
    }

    Destination->OnDestinationReached.RemoveAll(Destination);
    Destination->Destroy();
}