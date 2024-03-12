// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAbilitySystemComponent.h"
#include "CharacterAttributeSetBase.h"

void UCharacterAbilitySystemComponent::ReceiveDamage(UCharacterAbilitySystemComponent* SourceASC, float DamageValue)
{
    ReceivedDamage.Broadcast(SourceASC, DamageValue);
}