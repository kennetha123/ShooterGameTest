#include "QuestObjective.h"

void UQuestObjectiveDataAsset::IncrementKillCount()
{
    if (ObjectiveType == EObjectiveType::KillEnemies)
    {
        CurrentKillCount++;
    }
}

bool UQuestObjectiveDataAsset::IsObjectiveComplete() const
{
    if (ObjectiveType == EObjectiveType::KillEnemies)
    {
        return CurrentKillCount >= NumberOfEnemiesToKill;
    }

    return false;
}
