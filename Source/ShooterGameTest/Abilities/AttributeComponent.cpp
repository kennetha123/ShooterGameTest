// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeComponent.h"
#include "ShooterGameTest/ShooterGameTestCharacterBase.h"

void UAttributeComponent::ApplyDamage(AActor* Actor, float Amount)
{
	AShooterGameTestCharacterBase* Character = Cast<AShooterGameTestCharacterBase>(Actor);

	float NewHealth = Character->GetHealth() - 50.0f;
	Character->SetHealth(FMath::Max(NewHealth, 0.0f));

	if (!IsAlive())
	{
		OnDeath.Broadcast();
	}
}

bool UAttributeComponent::IsAlive() const
{
	return Health.GetCurrentValue() > 0.0f;
}
