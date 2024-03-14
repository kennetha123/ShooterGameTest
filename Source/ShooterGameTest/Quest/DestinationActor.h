#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>
#include "DestinationActor.generated.h"

class AQuestManager;

UCLASS()
class SHOOTERGAMETEST_API ADestinationActor : public AActor
{
	GENERATED_BODY()

public:
	ADestinationActor();

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnDestinationReached, ADestinationActor*);
	FOnDestinationReached OnDestinationReached;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* CollisionComponent;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
