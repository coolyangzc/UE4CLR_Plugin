// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using System.IO;
using UnrealBuildTool;

public class UE4CLR : ModuleRules
{
	public UE4CLR(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
		string NETCoreNativePath = Path.Combine(PluginDirectory, "Runtime/Win64/packs/Microsoft.NETCore.App.Host.win-x64/5.0.7/runtimes/win-x64/native");
		PublicIncludePaths.Add(NETCoreNativePath);

		PublicAdditionalLibraries.Add(Path.Combine(NETCoreNativePath, "nethost.lib"));

		if (Target.bBuildEditor)
		{
			PrivateDependencyModuleNames.AddRange(new string[] {
				"UnrealEd"
			});
		}

		string runtimePath = Path.Combine(PluginDirectory, "Runtime/Win64");

		string[] files = Directory.GetFiles(runtimePath, "*.*", SearchOption.AllDirectories);

		foreach (string file in files)
		{
			RuntimeDependencies.Add(file);
		}

	}
}
