// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EAbilityID : uint8
{
    None UMETA(DisplayName = "None"),
    Dash UMETA(DisplayName = "Dash"),
    Smoke UMETA(DisplayName = "Smoke"),
};