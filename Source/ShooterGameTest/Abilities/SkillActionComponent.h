#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillData.h"
#include "SkillActionComponent.generated.h"

class AShooterGameTestCharacterBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERGAMETEST_API USkillActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USkillActionComponent();

	virtual void ExecuteSkill(AShooterGameTestCharacterBase* Character);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	float Cooldown = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	USkillDataAsset* SkillDataAsset;

protected:
	virtual void StartCooldownTimer();

	bool bIsOnCooldown = false;

};

UCLASS()
class UDashComponent : public USkillActionComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dash")
	float DashSpeed = 2000.0f; 


	virtual void ExecuteSkill(AShooterGameTestCharacterBase* Character) override;
};

class UParticleSystemComponent;

UCLASS()
class USmokeComponent : public USkillActionComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Smoke")
	float SmokeDuration = 5.0f;

	virtual void ExecuteSkill(AShooterGameTestCharacterBase* Character) override;
	void DeactivateSmoke();
};