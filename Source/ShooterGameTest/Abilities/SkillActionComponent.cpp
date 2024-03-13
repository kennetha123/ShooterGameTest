// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillActionComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ShooterGameTest/ShooterGameTestCharacterBase.h"
#include <Kismet/GameplayStatics.h>
#include "Particles/ParticleSystemComponent.h"

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

    FTimerHandle CooldownTimer;
    GetWorld()->GetTimerManager().SetTimer(CooldownTimer, [&]()
        {
           bIsOnCooldown = false;
        }, 
        Cooldown, false);
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

void USmokeComponent::ExecuteSkill(AShooterGameTestCharacterBase* Character)
{
    Super::ExecuteSkill(Character);

    if (!Character) 
    { 
        return; 
    }

    SkillData = Character->SkillDataMap["Smoke"];



    UWorld* World = GetWorld();
    if (World && SkillData->SkillParticleSystem)
    {
        UE_LOG(LogTemp, Log, TEXT("Smoke Executed"));

        FVector ForwardVector = Character->GetActorForwardVector();
        FVector SpawnLocation = Character->GetActorLocation();
        FRotator SpawnRotation = Character->GetActorRotation();

        UGameplayStatics::SpawnEmitterAtLocation(World, SkillData->SkillParticleSystem, SpawnLocation, SpawnRotation);
    }

    FTimerHandle ExpiryTimer;
    GetWorld()->GetTimerManager().SetTimer(ExpiryTimer, this, &USmokeComponent::DeactivateSmoke, SmokeDuration, false);
}

void USmokeComponent::DeactivateSmoke()
{

}
