// Some copyright should be here...

using UnrealBuildTool;
using System.IO;

public class ManusVR : ModuleRules
{
    private string ModulePath
    {
        get { return Path.GetDirectoryName(RulesCompiler.GetModuleFilename(this.GetType().Name)); }
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
					"ManusVT/Public",
					// ... add public include paths required here ...
				}
            );

        PrivateIncludePaths.AddRange(
            new string[] {
					"ManusVR/Private",
                    Path.Combine(ThirdPartyPath, "Manus", "include"),
					// ... add other private include paths required here ...
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
				
				// ... add other public dependencies that you statically link with here ...
			}
            );





        PrivateDependencyModuleNames.AddRange(
            new string[]
				{
					// ... add private dependencies that you statically link with here ...
				}
            );

        DynamicallyLoadedModuleNames.AddRange(
            new string[]
				{
					// ... add any modules that your module loads dynamically here ...
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

            PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, PlatformString, "Manus.lib"));
            RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(LibraryPath, PlatformString, "Manus.dll")));
        }


        return isLibrarySupported;
    }

}
