#include "DestinationObjective.h"
#include "QuestObjective.h"
#include <Kismet/GameplayStatics.h>
#include "DestinationActor.h"

void UDestinationObjective::Initialize(UQuestObjectiveDataAsset* ObjectiveData)
{
    ObjectiveDataAsset = ObjectiveData;

    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), ObjectiveDataAsset->DestinationTag, FoundActors);
    UE_LOG(LogTemp, Log, TEXT("Found reach location quest."));

    for (auto Actor : FoundActors)
    {
        UE_LOG(LogTemp, Log, TEXT("found."));
        ADestinationActor* DestinationActor = Cast<ADestinationActor>(Actor);
        if (DestinationActor)
        {
            UE_LOG(LogTemp, Log, TEXT("bind."));
            if (OnLocationReached.IsBound())
            {
                DestinationActor->OnDestinationReached = OnLocationReached;
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Need to initialize OnLocationReached first before call Initialize function!"));
            }
        }
    }
}

void UDestinationObjective::UpdateProgress(AActor* Actor)
{
    if (!Actor || bIsComplete)
    {
        return;
    }

    bIsComplete = true;
}

bool UDestinationObjective::IsComplete() const
{
    return bIsComplete;
}

FString UDestinationObjective::GetTitle() const
{
    return ObjectiveDataAsset->Title;
}

FString UDestinationObjective::GetDescription() const
{
    return ObjectiveDataAsset->Description;
}
