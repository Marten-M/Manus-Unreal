// Copyright 2015 Manus Machina

#include "ManusVRPrivatePCH.h"
#include "ManusVRAnimInstance.h"


#include <Runtime/Engine/Classes/Animation/AnimNodeBase.h> //  Needed for Animation Evaluation in C++


DEFINE_LOG_CATEGORY(LogManusVRAnimation);
#define LOCTEXT_NAMESPACE "FManusVRModule"

//////////////////////////////////////////////////////////////////////////
// UManusVRAnimInstance

UManusVRAnimInstance::UManusVRAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UManusVRAnimInstance::getLeftHandFingers(TArray<float>& OutFingers)
{
	GLOVE_DATA data;
	int retval = retval = ManusGetData(GLOVE_LEFT, &data);
	if (MANUS_SUCCESS == retval) {
		OutFingers.Append(data.Fingers, 5);
	}
}

void UManusVRAnimInstance::getRightHandFingers(TArray<float>& OutFingers)
{
	GLOVE_DATA data;
	int retval = retval = ManusGetData(GLOVE_RIGHT, &data);
	if (MANUS_SUCCESS == retval) {
		OutFingers.Append(data.Fingers, 5);
	}
}

FRotator UManusVRAnimInstance::GetLeftHandRotation(){
	GLOVE_DATA data;
	int retval = retval = ManusGetData(GLOVE_LEFT, &data);
	if (MANUS_SUCCESS == retval) {
		return FRotator(FQuat(data.Quaternion.x, data.Quaternion.y, data.Quaternion.z, data.Quaternion.w));
	}
	return FRotator();
}

FRotator UManusVRAnimInstance::GetRightHandRotation(){
	GLOVE_DATA data;
	int retval = retval = ManusGetData(GLOVE_RIGHT, &data);
	if (MANUS_SUCCESS == retval) {
		return FRotator(FQuat(data.Quaternion.x, data.Quaternion.y, data.Quaternion.z, data.Quaternion.w));
	}
	return FRotator();
}


bool UManusVRAnimInstance::NativeEvaluateAnimation(struct FPoseContext& Output)
{
	if (useBlueprint) return false;
	if (HandAnimation == NULL)
	{
		UE_LOG(LogManusVRAnimation, Error, TEXT("Animation not set for %s glove"), isLeft ? "left" : "right");
		return true;
	}
	if (RootNode != NULL)
	{	
		GLOVE_DATA data;
		int retval = ManusGetData(isLeft ? GLOVE_LEFT: GLOVE_RIGHT, &data);
		if (retval != MANUS_SUCCESS){
			Output.ResetToRefPose();
			UE_LOG(LogManusVRAnimation, Error, TEXT("Unable to obtain data from %s glove"), isLeft ? "left" : "right");
		}

		float fAnimationLength = HandAnimation->GetPlayLength();
		
		FCompactPose pose;
		FBlendedCurve curve;
		for (int i = 0; i < 5; i++) 
		{
			FCompactPose pose;
			FBlendedCurve curve;
			pose.CopyBonesFrom(Output.Pose);
			curve.CopyFrom(Output.Curve);
			HandAnimation->GetAnimationPose(pose, curve, FAnimExtractContext(data.Fingers[i] * fAnimationLength));
			FQuat palmRotation(-data.Quaternion.x, data.Quaternion.y, data.Quaternion.z, -data.Quaternion.w);
			
			auto bc = Output.Pose.GetBoneContainer();
			
			FCompactPoseBoneIndex cpbi(0);
			
			if (isLeft)
				cpbi = FCompactPoseBoneIndex(bc.GetPoseBoneIndexForBoneName("Leapmotion_Basehand_Rig_Left"));
			else
				cpbi = FCompactPoseBoneIndex(bc.GetPoseBoneIndexForBoneName("Leapmotion_Basehand_Rig_Right"));
			
			if (Output.Pose[cpbi].IsValid()) Output.Pose[cpbi].SetRotation(palmRotation * FQuat(-1, 1, -1, 1));
			
			if (bc.IsValid()) {
				char boneName[] = "finger_00";
				boneName[7] = '0' + i; 
				for (int j = 0; j < 4; j++) {
					boneName[8] = '0' + j;
					FCompactPoseBoneIndex cpbi(bc.GetPoseBoneIndexForBoneName(boneName));
					if (Output.Pose[cpbi].IsValid()) Output.Pose[cpbi].SetRotation(pose[cpbi].GetRotation());
				}
			}
		}	
	}
	else
	{
		Output.ResetToRefPose();
		UE_LOG(LogManusVRAnimation, Warning, TEXT("RootNode==NULL"));
	}
	return true; 
}