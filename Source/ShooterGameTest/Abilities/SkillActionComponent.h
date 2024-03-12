#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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


protected:
	virtual void StartCooldownTimer();

	bool bIsOnCooldown = false;

	FTimerHandle CooldownTimer;
private:

};

UCLASS()
class UDashComponent : public USkillActionComponent
{
	GENERATED_BODY()

public:
	UDashComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dash")
	float DashSpeed = 2000.0f; 


	virtual void ExecuteSkill(AShooterGameTestCharacterBase* Character) override;

	virtual void StartCooldownTimer() override;

};