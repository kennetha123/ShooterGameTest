
#include "QuestManager.h"

void AQuestManager::OnEnemyKilled(AActor* Enemy)
{
    UE_LOG(LogTemp, Log, TEXT("OnEnemyKilled"));

    for (auto& Objective : Quests->Objectives)
    {
        if (Objective->ObjectiveType == EObjectiveType::KillEnemies)
        {
            EnemyKillCount++;
            UE_LOG(LogTemp, Log, TEXT("Quest : enemy remaining : %d / %d!"), EnemyKillCount, Objective->NumberOfEnemiesToKill);

            if (EnemyKillCount >= Objective->NumberOfEnemiesToKill)
            {
                UE_LOG(LogTemp, Log, TEXT("Quest : %s has been completed!"), *Objective->Title);
            }
        }
    }
}