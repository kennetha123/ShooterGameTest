#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "UTP_GravityComponent.generated.h"


UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTERGAMETEST_API UTP_GravityComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UTP_GravityComponent();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputMappingContext* GravityGunContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputAction* HoldObjectAction;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    class UInputAction* ReleaseObjectAction;

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    void PerformRaycast();

    void PickUpObject(AActor* ObjectToPickUp);

    void ReleaseObject();

    // Current object being held by the gravity gun
    AActor* PickedUpObject;

    // Physics handle used to manipulate objects
    UPROPERTY(EditAnywhere)
    UPhysicsHandleComponent* PhysicsHandle;

    // Whether the left mouse button is held down
    bool HoldLeftMouseButton;

    // Distance for ray tracing to pick up objects
    UPROPERTY(EditAnywhere)
    float TraceDistance;
};
