// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillActionComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ShooterGameTest/ShooterGameTestCharacterBase.h"

USkillActionComponent::USkillActionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USkillActionComponent::ExecuteSkill(AShooterGameTestCharacterBase* Character)
{
}

void USkillActionComponent::StartCooldownTimer()
{
    bIsOnCooldown = true;

    GetWorld()->GetTimerManager().SetTimer(CooldownTimer, [&]() 
        {
           bIsOnCooldown = false;
        }, 
        Cooldown, false);
}

UDashComponent::UDashComponent()
{
}

void UDashComponent::ExecuteSkill(AShooterGameTestCharacterBase* Character)
{
    Super::ExecuteSkill(Character);

    UE_LOG(LogTemp, Log, TEXT("Dash Executed"));
    if (!Character || bIsOnCooldown)
    {
        return;
    }

    Character->LaunchCharacter(Character->GetActorForwardVector() * DashSpeed, false, true);

    StartCooldownTimer();
}

void UDashComponent::StartCooldownTimer()
{
    Super::StartCooldownTimer();
}
