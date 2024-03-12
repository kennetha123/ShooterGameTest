// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

class IDamageable
{
public:
	virtual void ApplyDamage(AActor* Actor, float Amount) = 0;
	virtual bool IsAlive() const = 0;
};

UCLASS()
class SHOOTERGAMETEST_API UAttributeComponent : public UActorComponent, public IDamageable
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, Category= "Damage")
	FGameplayAttributeData Damage;

	virtual void ApplyDamage(AActor* Actor, float Amount) override;

	virtual bool IsAlive() const override;

public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDeath OnDeath;
};
