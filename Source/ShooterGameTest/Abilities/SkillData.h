// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillData.generated.h"

class USkillActionComponent;

USTRUCT(BlueprintType)
struct FSkillData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
    UTexture2D* Icon;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
    float Cooldown;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
    TWeakObjectPtr<USkillActionComponent> SkillActions;
};