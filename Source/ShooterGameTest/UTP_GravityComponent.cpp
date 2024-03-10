#include "UTP_GravityComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values for this component's properties
UTP_GravityComponent::UTP_GravityComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UTP_GravityComponent::BeginPlay()
{
    Super::BeginPlay();

    // Find the PhysicsHandle and make sure it exists
    TArray<UPhysicsHandleComponent*> Comps;
    GetOwner()->GetComponents(Comps);
    if (Comps.Num() > 0)
    {
        PhysicsHandle = Comps[0];
    }

    if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController<APlayerController>())
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(GravityGunContext, 1);
        }
    }

    // Bind Input Actions
    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(GetOwner()->InputComponent))
    {
        EnhancedInputComponent->BindAction(HoldObjectAction, ETriggerEvent::Started, this, &UTP_GravityComponent::PerformRaycast);
        EnhancedInputComponent->BindAction(ReleaseObjectAction, ETriggerEvent::Completed, this, &UTP_GravityComponent::ReleaseObject);
    }
}

// Called every frame
void UTP_GravityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    UE_LOG(LogTemp, Log, TEXT("PICKUPOBJECT : %d || PHYSICSHANDLE : %d"), PickedUpObject != nullptr, PhysicsHandle != nullptr);

    if (PickedUpObject && PhysicsHandle)
    {
        UE_LOG(LogTemp, Log, TEXT("Got Object: %s"), *PickedUpObject->GetHumanReadableName());
        PhysicsHandle->GrabComponentAtLocationWithRotation(
            PickedUpObject->FindComponentByClass<UStaticMeshComponent>(),
            NAME_None,
            PickedUpObject->GetActorLocation(),
            PickedUpObject->GetActorRotation()
        );
        UE_LOG(LogTemp, Log, TEXT("Attempted to grab object"));

        FVector Vec = FVector(1550.0, 840.0, 60.0);
        PhysicsHandle->SetTargetLocation(Vec);
    }
}

void UTP_GravityComponent::PerformRaycast()
{
    FHitResult HitResult;
    UCameraComponent* Camera = GetOwner()->FindComponentByClass<UCameraComponent>();

    // Perform raycast from the camera
    if (Camera)
    {
        FVector Start = Camera->GetComponentLocation();
        FVector End = Start + Camera->GetForwardVector() * TraceDistance;

        bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);

        if (bHit && HitResult.GetActor())// && HitResult.GetActor()->Tags.Contains("Pickupable"))
        {
            PickUpObject(HitResult.GetActor());
        }
    }
}

void UTP_GravityComponent::PickUpObject(AActor* ObjectToPickUp)
{
    UE_LOG(LogTemp, Log, TEXT("Pick up object"));

    PickedUpObject = ObjectToPickUp;
}

void UTP_GravityComponent::ReleaseObject()
{
    UE_LOG(LogTemp, Log, TEXT("Release Object"));

    if (PhysicsHandle)
    {
        PhysicsHandle->ReleaseComponent();
    }
    PickedUpObject = nullptr;
}