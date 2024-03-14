// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ShooterGameTest : ModuleRules
{
	public ShooterGameTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
		PrivateDependencyModuleNames.AddRange(new string[] { "GameplayAbilities" });
	}
}
