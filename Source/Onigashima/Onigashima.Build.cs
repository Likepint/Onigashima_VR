// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Onigashima : ModuleRules
{
	public Onigashima(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.Add(ModuleDirectory);
	
        PublicDependencyModuleNames.Add("Core");
        PrivateDependencyModuleNames.Add("CoreUObject");
        PrivateDependencyModuleNames.Add("Engine");
        PrivateDependencyModuleNames.Add("InputCore");

		PublicDependencyModuleNames.Add("EnhancedInput");

        PublicDependencyModuleNames.Add("UMG");

        PublicDependencyModuleNames.Add("Niagara");

        PublicDependencyModuleNames.Add("AIModule");
        PublicDependencyModuleNames.Add("GameplayTasks");
        PublicDependencyModuleNames.Add("NavigationSystem");

        PublicDependencyModuleNames.Add("ProceduralMeshComponent");

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
