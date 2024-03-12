#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "Abilities/AbilityEnums.h"
#include "Abilities/AttributeComponent.h"
#include "Abilities/SkillData.h"
#include "ShooterGameTestCharacterBase.generated.h"

UCLASS()
class SHOOTERGAMETEST_API AShooterGameTestCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterGameTestCharacterBase();

	UFUNCTION(BlueprintCallable, Category = "Character|Attributes")
	float GetHealth() const;

	virtual void SetHealth(float Health);

	TWeakObjectPtr<class UAttributeComponent> AttributeComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
	TArray<FSkillData> AvailableSkills;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
	FText CharacterName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animation")
	UAnimMontage* DeathMontage;

	virtual void SetMaxHealth(float MaxHealth);

private:
	void OnCharacterDeath();
};
