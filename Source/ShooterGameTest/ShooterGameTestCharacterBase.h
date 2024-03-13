#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "Abilities/AbilityEnums.h"
#include "Abilities/AttributeComponent.h"
#include "Abilities/SkillData.h"
#include "Abilities/SkillActionComponent.h"
#include "ShooterGameTestCharacterBase.generated.h"

UCLASS()
class SHOOTERGAMETEST_API AShooterGameTestCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AShooterGameTestCharacterBase();

	UFUNCTION(BlueprintCallable, Category = "Character|Attributes")
	float GetHealth() const;

	virtual void SetHealth(float Health);

	TWeakObjectPtr<class UAttributeComponent> AttributeComponent;

	TMap<FString, TWeakObjectPtr<USkillActionComponent>> AvailableSkills;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
	TMap<FString, USkillDataAsset*> SkillsData;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
	FText CharacterName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Animation")
	UAnimMontage* DeathMontage;

	USkillActionComponent* GetOrCreateSkillComponent(const FString& SkillName);

private:
	UFUNCTION()
	void OnCharacterDeath();

};
