#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Engine/DataAsset.h"
#include "SkillData.generated.h"

class UTexture2D;
class UParticleSystem;

USTRUCT(BlueprintType)
struct FSkillData
{
    GENERATED_BODY()

    // Skill name
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
    FString Name;

    // Skill icon
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
    UTexture2D* Icon;

    // Skill cooldown time
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
    float Cooldown;

    // Particle system associated with the skill
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
    UParticleSystem* SkillParticleSystem;
};

UCLASS()
class SHOOTERGAMETEST_API USkillDataAsset : public UDataAsset
{
    GENERATED_BODY()

public:
    // Array to store multiple skills' data
    UPROPERTY(EditAnywhere)
    TArray<FSkillData> SkillsData;
};
