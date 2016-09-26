// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
// Copyright 2015 Manus VR

using UnrealBuildTool;
using System.IO;

public class ManusVR : ModuleRules
{
    private string ModulePath
    {
        get { return ModuleDirectory; }
    }

    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/")); }
    }

    private string BinariesPath
    {
        get { return Path.GetFullPath(Path.Combine(ModulePath, "../../Binaries/")); }
    }

    private string LibraryPath
    {
        get { return Path.GetFullPath(Path.Combine(ThirdPartyPath, "Manus", "Lib")); }
    }

    public ManusVR(TargetInfo Target)
    {
        PublicIncludePaths.AddRange(
            new string[] {
					"ManusVR/Public",
				}
            );

        PrivateIncludePaths.AddRange(
            new string[] {
					"ManusVR/Private",
                    Path.Combine(ThirdPartyPath, "Manus", "include"),
				}
            );

        PublicDependencyModuleNames.AddRange(
            new string[]
			{
				"Engine",
				"Core",
                "CoreUObject",
                "InputCore",
                "Slate",
                "SlateCore",
			}
            );

        LoadManusLib(Target);
    }

    public bool LoadManusLib(TargetInfo Target)
    {
        bool isLibrarySupported = false;

        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
            isLibrarySupported = true;

            string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "Win64" : "Win32";

            string BaseDirectory = Path.GetFullPath(Path.Combine(ModuleDirectory, "..", ".."));
            string ManusDirectory = Path.Combine(BaseDirectory, "ThirdParty", "manus", "lib", PlatformString);

            RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(ManusDirectory, "Manus.dll")));
        }
        return isLibrarySupported;
    }

}
