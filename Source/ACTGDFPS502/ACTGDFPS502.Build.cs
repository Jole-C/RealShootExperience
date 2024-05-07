// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ACTGDFPS502 : ModuleRules
{
	public ACTGDFPS502(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "Niagara"});
	}
}
