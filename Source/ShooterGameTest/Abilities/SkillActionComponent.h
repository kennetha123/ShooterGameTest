#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillData.h"
#include "SkillActionComponent.generated.h"

// Forward declaration
class AShooterGameTestCharacterBase;

// Base class for skill action components
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTERGAMETEST_API USkillActionComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USkillActionComponent();

    // Function to execute a skill
    virtual void ExecuteSkill(AShooterGameTestCharacterBase* Character);

    // Skill data asset reference
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
    USkillDataAsset* SkillDataAsset;

protected:
    // Starts the cooldown timer
    virtual void StartCooldownTimer(float Cooldown);

    // Indicates whether the skill is on cooldown
    bool bIsOnCooldown = false;
};

// Component for dash skill actions
UCLASS()
class UDashComponent : public USkillActionComponent
{
    GENERATED_BODY()

public:
    // Speed of the dash
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dash")
    float DashSpeed = 2000.0f;

    // Executes the dash skill
    virtual void ExecuteSkill(AShooterGameTestCharacterBase* Character) override;
};

// Component for smoke skill actions
UCLASS()
class USmokeComponent : public USkillActionComponent
{
    GENERATED_BODY()

public:
    // Duration of the smoke effect
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Smoke")
    float SmokeDuration = 5.0f;

    // Executes the smoke skill
    virtual void ExecuteSkill(AShooterGameTestCharacterBase* Character) override;

    // Deactivates the smoke effect
    void DeactivateSmoke();
};
