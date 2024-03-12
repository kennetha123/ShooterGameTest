// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "ShooterGameTestCharacterBase.h"
#include "Abilities/CharacterAbilitySystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComponent->InitSphereRadius(75.0f);
	CollisionComponent->SetCollisionProfileName("Projectile");
	CollisionComponent->SetSimulatePhysics(false);

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AProjectile::OnOverlapEnd);
}

void AProjectile::BeginPlay()
{
    Super::BeginPlay();

}

void AProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor)
	{
		return;
	}

	if (OtherActor->ActorHasTag("Enemy"))
	{
		UE_LOG(LogTemp, Log, TEXT("Touch : %s"), *OtherActor->GetActorNameOrLabel());

		AShooterGameTestCharacterBase* Character = Cast<AShooterGameTestCharacterBase>(OtherActor);
		if (Character)
		{
			float NewHealth = Character->GetHealth() - 50.0f;
			Character->SetHealth(FMath::Max(NewHealth, 0.0f));
			UE_LOG(LogTemp, Log, TEXT("%s Health : %f"), *OtherActor->GetActorNameOrLabel(), Character->GetHealth());
			if (!Character->IsAlive())
			{
				Character->Die();
			}
		}
	}
}

void AProjectile::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor)
	{
		return;
	}

	if (OtherActor->ActorHasTag("Enemy"))
	{
		UE_LOG(LogTemp, Log, TEXT("Leave Touch %s!"), *OtherActor->GetActorNameOrLabel());
	}
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

