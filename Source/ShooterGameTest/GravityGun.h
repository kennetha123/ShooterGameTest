// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include <PhysicsEngine/PhysicsHandleComponent.h>
#include "GravityGun.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERGAMETEST_API UGravityGun : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGravityGun();

	UPROPERTY(EditAnywhere)
	FVector GravityGunPositionOffset;

	UPROPERTY(EditAnywhere)
	float MaxRaycastDistance = 400;

	UPROPERTY(EditAnywhere)
	float PickUpRadius = 100;

	UPROPERTY(EditAnywhere)
	float HoldDistance = 200;

	UPROPERTY(EditAnywhere)
	float LaunchForce = 3000;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* GravityGunMappingContext;

	/** Pick Up Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* PickUpAction;

	/** Release Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ReleaseAction;

	/** Launch Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LaunchAction;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void PickUp();
	
	void Release();

	void Launch();

	UPhysicsHandleComponent* PhysicsHandle;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
};
