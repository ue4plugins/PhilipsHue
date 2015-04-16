// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class PhilipsHue : ModuleRules
	{
		public PhilipsHue(TargetInfo Target)
		{
            DynamicallyLoadedModuleNames.AddRange(
                new string[] {
					"Settings",
				}
            );

			PrivateDependencyModuleNames.AddRange(
				new string[] {
					"Core",
                    "CoreUObject",
					"Http",
                    "Json",
					"Serialization",
				}
			);

            PrivateIncludePathModuleNames.AddRange(
                new string[] {
					"Settings",
				}
            );

			PrivateIncludePaths.AddRange(
				new string[] {
					"PhilipsHue/Private",
                    "PhilipsHue/Private/Bridges",
                    "PhilipsHue/Private/Groups",
                    "PhilipsHue/Private/Lights",
                    "PhilipsHue/Private/Shared",
				}
			);
		}
	}
}
