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

void USkillActionComponent::StartCooldownTimer(float Cooldown)
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

    if (!Character || bIsOnCooldown)
    {
        UE_LOG(LogTemp, Warning, TEXT("Character or Dash skill data not found."));
        return;
    }

    SkillDataAsset = Character->SkillsData;

    if (!SkillDataAsset)
    {
        UE_LOG(LogTemp, Warning, TEXT("Dash skill data asset is null."));
        return;
    }

    const FSkillData* DashSkillData = SkillDataAsset->SkillsData.FindByPredicate(
        [](const FSkillData& Data)
        {
            return Data.Name.Equals("Dash");
        }
    );

    Character->LaunchCharacter(Character->GetActorForwardVector() * DashSpeed, false, true);

    StartCooldownTimer(DashSkillData->Cooldown);
}

void USmokeComponent::ExecuteSkill(AShooterGameTestCharacterBase* Character)
{
    Super::ExecuteSkill(Character);

    if (!Character || bIsOnCooldown)
    {
        UE_LOG(LogTemp, Warning, TEXT("Character or Smoke skill data not found."));
        return;
    }

    SkillDataAsset = Character->SkillsData;

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
        FVector ForwardVector = Character->GetActorForwardVector();
        FVector SpawnLocation = Character->GetActorLocation();
        FRotator SpawnRotation = Character->GetActorRotation();

        UGameplayStatics::SpawnEmitterAtLocation(World, SmokeSkillData->SkillParticleSystem, SpawnLocation, SpawnRotation);
    }

    FTimerHandle ExpiryTimer;
    GetWorld()->GetTimerManager().SetTimer(ExpiryTimer, this, &USmokeComponent::DeactivateSmoke, SmokeSkillData->Cooldown, false);

    StartCooldownTimer(SmokeSkillData->Cooldown);
}

void USmokeComponent::DeactivateSmoke()
{

}
