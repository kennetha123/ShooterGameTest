// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActorComponent.h"
#include "Abilities/CharacterAbilitySystemComponent.h"

// Sets default values for this component's properties
AEnemyActorComponent::AEnemyActorComponent()
{
	AbilitySystemComponent = CreateDefaultSubobject<UCharacterAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	Tags.Add("Enemy");
}

// Called when the game starts
void AEnemyActorComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AttributeSetBase == nullptr)
	{
		AttributeSetBase = NewObject<UCharacterAttributeSetBase>(this, TEXT("AttributeSet"));
	}

	SetHealth(120.f);
}

UAbilitySystemComponent* AEnemyActorComponent::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}