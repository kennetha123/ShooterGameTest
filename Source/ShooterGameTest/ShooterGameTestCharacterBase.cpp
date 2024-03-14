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

void AShooterGameTestCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (AttributeComponent.IsValid() && !AttributeComponent->OnDeath.IsBound())
	{
		AttributeComponent->OnDeath.AddDynamic(this, &AShooterGameTestCharacterBase::OnCharacterDeath);
	}
}

void AShooterGameTestCharacterBase::OnCharacterDeath()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	UE_LOG(LogTemp, Log, TEXT("Character Death: %s is now dead."), *GetOwner()->GetActorNameOrLabel());

	if (DeathMontage)
	{
		PlayAnimMontage(DeathMontage);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Character Death: %s is being destroyed due to lack of DeathMontage."), *GetOwner()->GetActorNameOrLabel());
		Destroy();
	}
}

void AShooterGameTestCharacterBase::SetHealth(float Health)
{
	if (!AttributeComponent.IsValid())
	{
		return;
	}

	AttributeComponent->Health.SetCurrentValue(Health);
}

USkillActionComponent* AShooterGameTestCharacterBase::GetOrCreateSkillComponent(const FString& SkillName)
{
	TWeakObjectPtr<USkillActionComponent>* ComponentPtr = AvailableSkills.Find(SkillName);
	if (ComponentPtr && ComponentPtr->IsValid())
	{
		return ComponentPtr->Get();
	}
	else
	{
		USkillActionComponent* NewSkill = nullptr;

		if (SkillName == "Smoke")
		{
			NewSkill = NewObject<USmokeComponent>(this);
		}
		else if (SkillName == "Dash")
		{
			NewSkill = NewObject<UDashComponent>(this);
		}

		if (NewSkill)
		{
			NewSkill->RegisterComponent();
			AvailableSkills.Add(SkillName, NewSkill);
		}

		return NewSkill;
	}
}

