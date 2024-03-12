// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShooterGameTestCharacterBase.h"
#include "EnemyActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERGAMETEST_API AEnemyActorComponent : public AShooterGameTestCharacterBase
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	AEnemyActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;		
};
