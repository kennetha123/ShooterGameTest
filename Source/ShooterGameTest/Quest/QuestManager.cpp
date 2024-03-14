
#include "QuestManager.h"

void AQuestManager::OnEnemyKilled(AActor* Enemy)
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