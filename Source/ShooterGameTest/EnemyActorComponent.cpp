// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActorComponent.h"
#include "ShooterGameTest/ShooterGameTestGameInstance.h"
#include "Quest/QuestManager.h"
#include <Kismet/GameplayStatics.h>

AEnemyActorComponent::AEnemyActorComponent()
{
	Tags.Add("Enemy");
}

// Called when the game starts
void AEnemyActorComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHealth(120.f);
}

void AEnemyActorComponent::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (AttributeComponent == nullptr)
	{
		AttributeComponent = NewObject<UAttributeComponent>(this, TEXT("AttributeSet"));
	}
}

void AEnemyActorComponent::OnCharacterDeath()
{
	Super::OnCharacterDeath();

	OnEnemyKilled.Broadcast(this);
}
