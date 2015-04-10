// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class PhilipsHue : ModuleRules
	{
		public PhilipsHue(TargetInfo Target)
		{
			PrivateDependencyModuleNames.AddRange(
				new string[] {
					"Core",
                    "CoreUObject",
					"Http",
					"Serialization",
				}
			);

			PrivateIncludePaths.AddRange(
				new string[] {
					"PhilipsHue/Private",
				}
			);
		}
	}
}
