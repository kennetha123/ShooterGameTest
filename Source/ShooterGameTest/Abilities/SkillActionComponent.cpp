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

    if (!Character || !Character->SkillsData.Contains("Smoke"))
    {
        UE_LOG(LogTemp, Warning, TEXT("Character or Smoke skill data not found."));
        return;
    }

    SkillDataAsset = Character->SkillsData["Smoke"];

    if (!SkillDataAsset)
    {
        UE_LOG(LogTemp, Warning, TEXT("Smoke skill data asset is null."));
        return;
    }

    const FSkillData* SmokeSkillData = SkillDataAsset->SkillsData.FindByPredicate(
        [](const FSkillData& Data) 
        {
            return Data.Name.Equals("Smoke");
        }
    );

    if (!SmokeSkillData || !SmokeSkillData->SkillParticleSystem)
    {
        UE_LOG(LogTemp, Warning, TEXT("Smoke skill data or particle system not found."));
        return;
    }

    UWorld* World = GetWorld();
    if (World)
    {
        UE_LOG(LogTemp, Log, TEXT("Smoke Executed"));

        FVector ForwardVector = Character->GetActorForwardVector();
        FVector SpawnLocation = Character->GetActorLocation();
        FRotator SpawnRotation = Character->GetActorRotation();

        UGameplayStatics::SpawnEmitterAtLocation(World, SmokeSkillData->SkillParticleSystem, SpawnLocation, SpawnRotation);
    }

    FTimerHandle ExpiryTimer;
    GetWorld()->GetTimerManager().SetTimer(ExpiryTimer, this, &USmokeComponent::DeactivateSmoke, SmokeSkillData->Cooldown, false);

    StartCooldownTimer();
}

void USmokeComponent::DeactivateSmoke()
{

}
