// Copyright 2015 Manus Machina

#include "ManusVRPrivatePCH.h"
#include "Manus.h"
#include "ManusVRController.h"

DEFINE_LOG_CATEGORY(LogManusVRController);
#define LOCTEXT_NAMESPACE "FManusVRModule"

//UE v4.6 IM event wrappers
bool EmitKeyUpEventForKey(FKey key, int32 user, bool repeat)
{
	FKeyEvent KeyEvent(key, FSlateApplication::Get().GetModifierKeys(), user, repeat, 0, 0);
	return FSlateApplication::Get().ProcessKeyUpEvent(KeyEvent);
}

bool EmitKeyDownEventForKey(FKey key, int32 user, bool repeat)
{
	FKeyEvent KeyEvent(key, FSlateApplication::Get().GetModifierKeys(), user, repeat, 0, 0);
	return FSlateApplication::Get().ProcessKeyDownEvent(KeyEvent);
}

bool EmitAnalogInputEventForKey(FKey key, float value, int32 user, bool repeat)
{
	FAnalogInputEvent AnalogInputEvent(key, FSlateApplication::Get().GetModifierKeys(), user, repeat, 0, 0, value);
	return FSlateApplication::Get().ProcessAnalogInputEvent(AnalogInputEvent);
}


UManusVRController::UManusVRController(const FObjectInitializer &init) : UActorComponent(init)
{
	bWantsInitializeComponent = true;
	bAutoActivate = true;
	PrimaryComponentTick.bCanEverTick = true;	//the component automatically ticks so we don't have to
}

void UManusVRController::TickComponent(float DeltaTime, enum ELevelTick TickType,
	FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	GLOVE_DATA data;
	int retval = retval = ManusGetData(GLOVE_LEFT, &data);
	if (MANUS_SUCCESS == retval) {
		// Note: There is a factor 3 in the values sent and received
		EmitAnalogInputEventForKey(EManus::Left_Thumb,  data.Fingers[0], 0, 0);
		EmitAnalogInputEventForKey(EManus::Left_Index,  data.Fingers[1], 0, 0);
		EmitAnalogInputEventForKey(EManus::Left_Middle, data.Fingers[2], 0, 0);
		EmitAnalogInputEventForKey(EManus::Left_Ring,   data.Fingers[3], 0, 0);
		EmitAnalogInputEventForKey(EManus::Left_Pinky,  data.Fingers[4], 0, 0);
	}

	retval = ManusGetData(GLOVE_RIGHT, &data);
	if (MANUS_SUCCESS == retval) {
		EmitAnalogInputEventForKey(EManus::Right_Thumb,  data.Fingers[0], 0, 0);
		EmitAnalogInputEventForKey(EManus::Right_Index,  data.Fingers[1], 0, 0);
		EmitAnalogInputEventForKey(EManus::Right_Middle, data.Fingers[2], 0, 0);
		EmitAnalogInputEventForKey(EManus::Right_Ring,   data.Fingers[3], 0, 0);
		EmitAnalogInputEventForKey(EManus::Right_Pinky,  data.Fingers[4], 0, 0);
	}
}
#undef LOCTEXT_NAMESPACE