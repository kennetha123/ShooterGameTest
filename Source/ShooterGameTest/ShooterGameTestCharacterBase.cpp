// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameTestCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "Abilities/CharacterAbilitySystemComponent.h"
#include "Abilities/CharacterGameplayAbility.h"

// Sets default values
AShooterGameTestCharacterBase::AShooterGameTestCharacterBase()
{
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Overlap);

	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
	EffectRemoveOnDeathTag = FGameplayTag::RequestGameplayTag(FName("State.RemoveOnDeath"));


}

bool AShooterGameTestCharacterBase::IsAlive() const
{
	return GetHealth() > 0.0f;
}

int32 AShooterGameTestCharacterBase::GetAbilityLevel(AbilityID Ability) const
{
	// always set to 1 as we don't have any ability level progression.
	return 1;
}

void AShooterGameTestCharacterBase::RemoveCharacterAbilities()
{
	if (!AbilitySystemComponent.IsValid() ||
		!AbilitySystemComponent->IsCharacterAbilitiesGiven)
	{
		return;
	}

	TArray<FGameplayAbilitySpecHandle> AbilitiesToRemove;
	for (const FGameplayAbilitySpec& Spec : AbilitySystemComponent->GetActivatableAbilities())
	{
		if (Spec.SourceObject == this && CharacterAbilities.Contains(Spec.Ability->GetClass()))
		{
			AbilitiesToRemove.Add(Spec.Handle);
		}
	}

	for (size_t i = 0; i < AbilitiesToRemove.Num(); i++)
	{
		AbilitySystemComponent->ClearAbility(AbilitiesToRemove[i]);
	}

	AbilitySystemComponent->IsCharacterAbilitiesGiven = false;
}

void AShooterGameTestCharacterBase::Die()
{
	RemoveCharacterAbilities();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	OnCharacterDied.Broadcast(this);

	if (AbilitySystemComponent.IsValid())
	{
		AbilitySystemComponent->CancelAbilities();

		FGameplayTagContainer EffectsTagToRemove;
		EffectsTagToRemove.AddTag(EffectRemoveOnDeathTag);
		int32 NumEffectsRemoved = AbilitySystemComponent->RemoveActiveEffectsWithTags(EffectsTagToRemove);
		AbilitySystemComponent->AddLooseGameplayTag(DeadTag);
	}

	if (DeathMontage)
	{
		PlayAnimMontage(DeathMontage);
	}
	else
	{
		CleanUpDie();
	}
}

void AShooterGameTestCharacterBase::CleanUpDie()
{
	Destroy();
}

float AShooterGameTestCharacterBase::GetHealth() const
{
	if (AttributeSetBase.IsValid())
	{
		return AttributeSetBase->Health.GetCurrentValue();
	}

	return 0.0f;
}

// Called when the game starts or when spawned
void AShooterGameTestCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AShooterGameTestCharacterBase::AddCharacterAbilities()
{
	if (!AbilitySystemComponent.IsValid() ||
		AbilitySystemComponent->IsCharacterAbilitiesGiven)
	{
		return;
	}

	for (TSubclassOf<UCharacterGameplayAbility>& StartAbility : CharacterAbilities)
	{
		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(StartAbility,
			GetAbilityLevel(StartAbility.GetDefaultObject()->AbilityIDs),
				static_cast<int32>(StartAbility.GetDefaultObject()->AbilityInputID), this));
	}

	AbilitySystemComponent->IsCharacterAbilitiesGiven = true;
}

void AShooterGameTestCharacterBase::InitializeAttributes()
{
	if (!AbilitySystemComponent.IsValid())
	{
		return;
	}

	if (!DefaultAttributes)
	{
		UE_LOG(LogTemp, Log, TEXT("Missing Default Attributes."));
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, 1, EffectContext);

	if (NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
	}
}

void AShooterGameTestCharacterBase::SetHealth(float Health)
{
	if (AttributeSetBase.IsValid())
	{
		AttributeSetBase->Health.SetCurrentValue(Health);
	}
}

UAbilitySystemComponent* AShooterGameTestCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

