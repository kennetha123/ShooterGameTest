#include "DestinationActor.h"
#include "ShooterGameTest/ShooterGameTestCharacter.h"

void ADestinationActor::BeginPlay()
{
	Super::BeginPlay();
}

ADestinationActor::ADestinationActor()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	RootComponent = CollisionComponent;

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ADestinationActor::OnOverlapBegin);
}

void ADestinationActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->IsA(AShooterGameTestCharacter::StaticClass()))
	{
		OnDestinationReached.Broadcast(this);
	}
}
