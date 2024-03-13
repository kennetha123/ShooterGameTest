// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActorComponent.h"

// Sets default values for this component's properties
AEnemyActorComponent::AEnemyActorComponent()
{
	if (AttributeComponent == nullptr)
	{
		AttributeComponent = NewObject<UAttributeComponent>(this, TEXT("AttributeSet"));
	}

	Tags.Add("Enemy");
}

// Called when the game starts
void AEnemyActorComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHealth(120.f);
}