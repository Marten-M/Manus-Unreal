// Copyright 2015 Manus VR

#include "ManusVRPrivatePCH.h"
#include "ManusVR.h"
#include "ManusVRController.h"
#include "ManusLib.h"

IMPLEMENT_MODULE(FManusVRModule, ManusVR)
DEFINE_LOG_CATEGORY(LogManusVR);
#define LOCTEXT_NAMESPACE "FManusVRModule"

int_void _ManusInit = NULL;
int_void _ManusExit = NULL;
int_hand_pdata_uint _ManusGetData = NULL;

const FKey EManus::Left_Palm("ManusLeftPalm");
const FKey EManus::Left_Thumb("ManusLeftThumb");
const FKey EManus::Left_Index("ManusLeftIndex");
const FKey EManus::Left_Middle("ManusLeftMiddle");
const FKey EManus::Left_Ring("ManusLeftRing");
const FKey EManus::Left_Pinky("ManusLeftPinky");

const FKey EManus::Right_Palm("ManusRightPalm");
const FKey EManus::Right_Thumb("ManusRightThumb");
const FKey EManus::Right_Index("ManusRightIndex");
const FKey EManus::Right_Middle("ManusRightMiddle");
const FKey EManus::Right_Ring("ManusRightRing");
const FKey EManus::Right_Pinky("ManusRightPinky");

void FManusVRModule::StartupModule()
{
	UE_LOG(LogManusVR, Error, TEXT("Initialising Manus Library"));

	FString filePath = FPaths::Combine(*FPaths::GamePluginsDir(), 
		TEXT("ManusVR/ThirdParty/Manus/lib"), 
		TEXT(PlatformString), 
		TEXT("Manus.dll"));

	if (FPaths::FileExists(filePath))
	{
		void *DLLHandle;
		DLLHandle = FPlatformProcess::GetDllHandle(*filePath); 
		if (DLLHandle != NULL)
		{
			FString procName = "ManusInit";
			_ManusInit = (int_void)FPlatformProcess::GetDllExport(DLLHandle, *procName);
			procName = "ManusExit";
			_ManusExit = (int_void)FPlatformProcess::GetDllExport(DLLHandle, *procName);
			procName = "ManusGetData";
			_ManusGetData = (int_hand_pdata_uint)FPlatformProcess::GetDllExport(DLLHandle, *procName);
		}
		else
		{
			UE_LOG(LogManusVR, Error, TEXT("Cannot Obtain DLL Handle"))
		}
	}
	else
	{
		UE_LOG(LogManusVR, Error, TEXT("Cannot Find DLL %s"), *filePath)
	}

	if (_ManusInit) {
		_ManusInit();

		EKeys::AddKey(FKeyDetails(EManus::Left_Palm, LOCTEXT("ManusLeftPalm", "ManusVR Left Palm"), FKeyDetails::VectorAxis, "Manus"));
		EKeys::AddKey(FKeyDetails(EManus::Left_Thumb, LOCTEXT("ManusLeftThumb", "ManusVR Left Thumb"), FKeyDetails::FloatAxis, "Manus"));
		EKeys::AddKey(FKeyDetails(EManus::Left_Index, LOCTEXT("ManusLeftIndex", "ManusVR Left Index"), FKeyDetails::FloatAxis, "Manus"));
		EKeys::AddKey(FKeyDetails(EManus::Left_Middle, LOCTEXT("ManusLeftMiddle", "ManusVR Left Middle"), FKeyDetails::FloatAxis, "Manus"));
		EKeys::AddKey(FKeyDetails(EManus::Left_Ring, LOCTEXT("ManusLeftRing", "ManusVR Left Ring"), FKeyDetails::FloatAxis, "Manus"));
		EKeys::AddKey(FKeyDetails(EManus::Left_Pinky, LOCTEXT("ManusLeftPinky", "ManusVR Left Pinky"), FKeyDetails::FloatAxis, "Manus"));

		EKeys::AddKey(FKeyDetails(EManus::Right_Palm, LOCTEXT("ManusRightPalm", "ManusVR Right Palm"), FKeyDetails::VectorAxis, "Manus"));
		EKeys::AddKey(FKeyDetails(EManus::Right_Thumb, LOCTEXT("ManusRightThumb", "ManusVR Right Thumb"), FKeyDetails::FloatAxis, "Manus"));
		EKeys::AddKey(FKeyDetails(EManus::Right_Index, LOCTEXT("ManusRightIndex", "ManusVR Right Index"), FKeyDetails::FloatAxis, "Manus"));
		EKeys::AddKey(FKeyDetails(EManus::Right_Middle, LOCTEXT("ManusRightMiddle", "ManusVR Right Middle"), FKeyDetails::FloatAxis, "Manus"));
		EKeys::AddKey(FKeyDetails(EManus::Right_Ring, LOCTEXT("ManusRightRing", "ManusVR Right Ring"), FKeyDetails::FloatAxis, "Manus"));
		EKeys::AddKey(FKeyDetails(EManus::Right_Pinky, LOCTEXT("ManusRightPinky", "ManusVR Right Pinky"), FKeyDetails::FloatAxis, "Manus"));
	}
}

void FManusVRModule::ShutdownModule()
{
	if (_ManusExit) _ManusExit();
}

#undef LOCTEXT_NAMESPACE
