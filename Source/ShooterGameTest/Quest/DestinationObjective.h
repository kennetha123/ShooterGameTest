// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>
#include "DestinationObjective.generated.h"

class AQuestManager;

UCLASS()
class SHOOTERGAMETEST_API ADestinationObjective : public AActor
{
	GENERATED_BODY()
	
public:	
	ADestinationObjective();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDestinationReached, ADestinationObjective*, DestinationObjective);
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDestinationReached OnDestinationReached;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* CollisionComponent;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
