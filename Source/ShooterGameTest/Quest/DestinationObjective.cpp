#include "DestinationObjective.h"
#include "ShooterGameTest/ShooterGameTestCharacter.h"

ADestinationObjective::ADestinationObjective()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	RootComponent = CollisionComponent;

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ADestinationObjective::OnOverlapBegin);
}

void ADestinationObjective::BeginPlay()
{
	Super::BeginPlay();
}

void ADestinationObjective::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(AShooterGameTestCharacter::StaticClass()))
	{
		OnDestinationReached.Broadcast(this);
	}
}
