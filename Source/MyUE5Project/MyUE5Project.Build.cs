// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyUE5Project : ModuleRules
{
	public MyUE5Project(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		// Add "AkAudio" and "PhysicsCore" to be able to use and compile Wwise's API and UPhysicalMaterial in C++
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore",
			"HeadMountedDisplay", "AkAudio", "PhysicsCore"});
	} 
}
