 // Fill out your copyright notice in the Description page of Project Settings.


#include "GravityGun.h"
#include "Engine/World.h"
#include <EnhancedInputSubsystems.h>
#include <EnhancedInputComponent.h>

// Sets default values for this component's properties
UGravityGun::UGravityGun()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGravityGun::BeginPlay()
{
	Super::BeginPlay();

	SetRelativeLocation(GravityGunPositionOffset);

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(GravityGunMappingContext, 0);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			EnhancedInputComponent->BindAction(PickUpAction, ETriggerEvent::Started, this, &UGravityGun::PickUp);
			EnhancedInputComponent->BindAction(ReleaseAction, ETriggerEvent::Completed, this, &UGravityGun::Release);
			EnhancedInputComponent->BindAction(LaunchAction, ETriggerEvent::Triggered, this, &UGravityGun::Launch);
		}
	}

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Log, TEXT("There is no Physics Handle!"));
	}
}

void UGravityGun::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		FVector TargetLocation = GetComponentLocation() + GetRightVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
}

void UGravityGun::PickUp()
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetRightVector() * MaxRaycastDistance;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(PickUpRadius);
	FHitResult HitResult;

	bool isHit = GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, Sphere);

	if (isHit)
	{
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitResult.GetComponent(),
			NAME_None,
			HitResult.ImpactPoint,
			HitResult.GetComponent()->GetComponentRotation()
		);
	}
}

void UGravityGun::Release()
{
	if (PhysicsHandle == nullptr)
	{
		return;
	}

	if (PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		PhysicsHandle->ReleaseComponent();
	}
}

void UGravityGun::Launch()
{
	if (PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		UPrimitiveComponent* GrabbedComponent = PhysicsHandle->GetGrabbedComponent();
		PhysicsHandle->ReleaseComponent();
		GrabbedComponent->AddImpulse(GetRightVector() * LaunchForce, NAME_None, true);
	}
}



