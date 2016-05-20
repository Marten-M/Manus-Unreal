ManusVR Unreal Plugin 
=====================


When adding the ManusVR Unreal Plugin to an existing Unreal project which uses the Unreal .gitignore template from github, take care to exclude from being ignored by git. Add the following lines to .gitignore

```
!Plugins/ManusVR/ThirdParty/Manus/lib/Win32/*
!Plugins/ManusVR/ThirdParty/Manus/lib/Win64/*
```

