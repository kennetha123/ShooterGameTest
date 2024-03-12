// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CharacterAbilitySystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FReceiveDamageDelegate, UCharacterAbilitySystemComponent*, SourceASC, float, DamageValue);

/**
 * 
 */
UCLASS()
class SHOOTERGAMETEST_API UCharacterAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	bool IsCharacterAbilitiesGiven = false;
	bool IsStatusEffectApplied = false;

	FReceiveDamageDelegate ReceivedDamage;

	virtual void ReceiveDamage(UCharacterAbilitySystemComponent* SourceASC, float DamageValue);
};
