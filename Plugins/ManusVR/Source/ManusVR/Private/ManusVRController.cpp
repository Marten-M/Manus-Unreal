// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
// Copyright 2015 Manus VR

#include "ManusVRPrivatePCH.h"
#include "ManusVRController.h"
#include "ManusLib.h"

DEFINE_LOG_CATEGORY(LogManusVRController);
#define LOCTEXT_NAMESPACE "FManusVRModule"

//UE v4.6 IM event wrappers
bool EmitKeyUpEventForKey(FKey Key, int32 User, bool bRepeat)
{
	FKeyEvent KeyEvent(Key, FSlateApplication::Get().GetModifierKeys(), User, bRepeat, 0, 0);
	return FSlateApplication::Get().ProcessKeyUpEvent(KeyEvent);
}

bool EmitKeyDownEventForKey(FKey Key, int32 User, bool bRepeat)
{
	FKeyEvent KeyEvent(Key, FSlateApplication::Get().GetModifierKeys(), User, bRepeat, 0, 0);
	return FSlateApplication::Get().ProcessKeyDownEvent(KeyEvent);
}

bool EmitAnalogInputEventForKey(FKey Key, float Value, int32 User, bool bRepeat)
{
	FAnalogInputEvent AnalogInputEvent(Key, FSlateApplication::Get().GetModifierKeys(), User, bRepeat, 0, 0, Value);
	return FSlateApplication::Get().ProcessAnalogInputEvent(AnalogInputEvent);
}


UManusVRController::UManusVRController(const FObjectInitializer &Init) : UActorComponent(Init)
{
	bWantsInitializeComponent = true;
	bAutoActivate = true;
	PrimaryComponentTick.bCanEverTick = true;	//the component automatically ticks so we don't have to
}

void UManusVRController::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (_ManusGetData) 
	{
		GLOVE_DATA Data;
		if (MANUS_SUCCESS == _ManusGetData(GLOVE_LEFT, &Data, 0))
		{
			// Note: There is a factor 3 in the values sent and received
			EmitAnalogInputEventForKey(EManus::Left_Thumb,  Data.Fingers[0], 0, 0);
			EmitAnalogInputEventForKey(EManus::Left_Index,  Data.Fingers[1], 0, 0);
			EmitAnalogInputEventForKey(EManus::Left_Middle, Data.Fingers[2], 0, 0);
			EmitAnalogInputEventForKey(EManus::Left_Ring,   Data.Fingers[3], 0, 0);
			EmitAnalogInputEventForKey(EManus::Left_Pinky,  Data.Fingers[4], 0, 0);
		}

		if (MANUS_SUCCESS == _ManusGetData(GLOVE_RIGHT, &Data, 0))
		{
			EmitAnalogInputEventForKey(EManus::Right_Thumb,  Data.Fingers[0], 0, 0);
			EmitAnalogInputEventForKey(EManus::Right_Index,  Data.Fingers[1], 0, 0);
			EmitAnalogInputEventForKey(EManus::Right_Middle, Data.Fingers[2], 0, 0);
			EmitAnalogInputEventForKey(EManus::Right_Ring,   Data.Fingers[3], 0, 0);
			EmitAnalogInputEventForKey(EManus::Right_Pinky,  Data.Fingers[4], 0, 0);
		}
	}
}
#undef LOCTEXT_NAMESPACE