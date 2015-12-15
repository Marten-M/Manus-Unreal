// Copyright 2015 Manus VR

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

    // https://github.com/fmod/ue4integration/blob/master/FMODStudio/Source/FMODStudio/FMODStudio.Build.cs
    private void CopyFile(string source, string dest)
    {
        if (System.IO.File.Exists(dest))
        {
            System.IO.File.SetAttributes(dest, System.IO.File.GetAttributes(dest) & ~System.IO.FileAttributes.ReadOnly);
        }
        try
        {
            System.IO.File.Copy(source, dest, true);
        }
        catch (System.Exception ex)
        {
            System.Console.WriteLine("Failed to copy file: {0}", ex.Message);
        }
    }

    public bool LoadManusLib(TargetInfo Target)
    {
        bool isLibrarySupported = false;

        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
            isLibrarySupported = true;

            string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "Win64" : "Win32";

            PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, PlatformString, "Manus.lib"));

            string From = Path.Combine(LibraryPath, PlatformString, "Manus.dll");
            string destPathEditor = (ModulePath + "/../../Binaries/" + PlatformString);
            string destPathRelease = (ModulePath + "/../../../../Binaries/" + PlatformString);

            System.IO.Directory.CreateDirectory(destPathEditor);
            System.IO.Directory.CreateDirectory(destPathRelease);
            destPathEditor += "/Manus.dll";
            destPathRelease += "/Manus.dll";
            CopyFile(From, destPathEditor);
            CopyFile(From, destPathRelease);
        }
        return isLibrarySupported;
    }

}
