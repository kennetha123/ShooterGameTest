#include "QuestManager.h"
#include "DestinationActor.h"
#include <Kismet/GameplayStatics.h>
#include <ShooterGameTest/EnemyActorComponent.h>
#include "KillEnemiesObjective.h"
#include "DestinationObjective.h"

void AQuestManager::BeginPlay()
{
    Super::BeginPlay();

    if (QuestsData == nullptr && QuestsData->Objectives.Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("Error : Quest is empty!"));
        return;
    }

    for (auto& QuestData : QuestsData->Objectives)
    {
        UE_LOG(LogTemp, Log, TEXT("Iterate through quest"));

        if (QuestData->ObjectiveType == EObjectiveType::ReachLocation)
        {
            UDestinationObjective* NewObjective = NewObject<UDestinationObjective>(this);

            // this is really hacky, i know.. but for now to pass the function without having
            // function pointer, I think this is the way to do it for now.
            NewObjective->OnLocationReached.AddUObject(this, &AQuestManager::OnLocationReached);
            NewObjective->Initialize(QuestData);
            QuestsObjective.Add(NewObjective);
        }
        else if (QuestData->ObjectiveType == EObjectiveType::KillEnemies)
        {
            UKillEnemiesObjective* NewObjective = NewObject<UKillEnemiesObjective>(this);

            NewObjective->OnEnemyKilled.AddUObject(this, &AQuestManager::OnEnemyKilled);
            NewObjective->Initialize(QuestData);
            QuestsObjective.Add(NewObjective);

        }
    }
}

void AQuestManager::OnEnemyKilled(AEnemyActorComponent* Enemy)
{
    UE_LOG(LogTemp, Log, TEXT("OnEnemyKilled"));

    for (UObject* Obj : QuestsObjective)
    {
        if (!IsValid(Obj))
        {
            UE_LOG(LogTemp, Warning, TEXT("Invalid object encountered in QuestsObjective."));
            continue;
        }

        UKillEnemiesObjective* KillObjective = Cast<UKillEnemiesObjective>(Obj);
        if (!KillObjective)
        {
            UE_LOG(LogTemp, Warning, TEXT("Object is not a UKillEnemiesObjective. Actual class: %s"), *Obj->GetClass()->GetName());
            continue;
        }

        if (KillObjective)
        {
            KillObjective->UpdateProgress();

            if (KillObjective->IsComplete())
            {
                UE_LOG(LogTemp, Log, TEXT("Quest : %s has been completed!"), *KillObjective->GetTitle());
                Enemy->OnEnemyKilled.RemoveAll(Enemy);
            }
        }
    }
}

void AQuestManager::OnLocationReached(ADestinationActor* Destination)
{
    UE_LOG(LogTemp, Log, TEXT("OnLocationReached"));

    // Loop through the quest objectives to find destination objectives
    for (UObject* Obj : QuestsObjective)
    {
        if (!IsValid(Obj))
        {
            UE_LOG(LogTemp, Warning, TEXT("Invalid object encountered in QuestsObjective."));
            continue;
        }

        UDestinationObjective* DestinationObjective = Cast<UDestinationObjective>(Obj);
        if (!DestinationObjective)
        {
            UE_LOG(LogTemp, Warning, TEXT("Object is not a DestinationObjective. Actual class: %s"), *Obj->GetClass()->GetName());
            continue;
        }

        if (DestinationObjective)
        {
            DestinationObjective->UpdateProgress(Destination);

            if (DestinationObjective->IsComplete())
            {
                UE_LOG(LogTemp, Log, TEXT("Quest : %s has been completed!"), *DestinationObjective->GetTitle());
                Destination->OnDestinationReached.RemoveAll(Destination);
                Destination->Destroy();

            }
        }
    }

}