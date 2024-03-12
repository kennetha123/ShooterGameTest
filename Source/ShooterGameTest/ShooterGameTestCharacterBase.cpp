// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameTestCharacterBase.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AShooterGameTestCharacterBase::AShooterGameTestCharacterBase()
{
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Overlap);
}

float AShooterGameTestCharacterBase::GetHealth() const
{
	if (AttributeComponent.IsValid())
	{
		return AttributeComponent->Health.GetCurrentValue();
	}

	return 0.0f;
}

// Called when the game starts or when spawned
void AShooterGameTestCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AShooterGameTestCharacterBase::SetMaxHealth(float MaxHealth)
{
	if (AttributeComponent.IsValid())
	{
		AttributeComponent->Health.SetBaseValue(MaxHealth);
		AttributeComponent->OnDeath.AddDynamic(this, &AShooterGameTestCharacterBase::OnCharacterDeath);
	}
}

void AShooterGameTestCharacterBase::OnCharacterDeath()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	UE_LOG(LogTemp, Log, TEXT("Character Dead %s"), *GetOwner()->GetActorNameOrLabel());
	if (DeathMontage)
	{
		PlayAnimMontage(DeathMontage);
	}
	else
	{
		Destroy();
	}
}

void AShooterGameTestCharacterBase::SetHealth(float Health)
{
	if (AttributeComponent.IsValid())
	{
		AttributeComponent->Health.SetCurrentValue(Health);
	}
}
