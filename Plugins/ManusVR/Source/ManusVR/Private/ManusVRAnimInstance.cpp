// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
// Copyright 2015 Manus VR

#include "ManusVRPrivatePCH.h"
#include "ManusVRAnimInstance.h"
#include <Runtime/Engine/Classes/Animation/AnimNodeBase.h> 

DEFINE_LOG_CATEGORY(LogManusVRAnimation);
#define LOCTEXT_NAMESPACE "FManusVRModule"

UManusVRAnimInstance::UManusVRAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if (ENGINE_MAJOR_VERSION >= 4) && (ENGINE_MINOR_VERSION >= 11)
	Proxy.ManusVRAnimInstance = this;
#endif
}

void UManusVRAnimInstance::GetLeftHandFingers(TArray<float>& OutFingers)
{
	if (_ManusGetData) 
	{
		GLOVE_DATA Data;
		if (MANUS_SUCCESS == _ManusGetData(GLOVE_LEFT, &Data, 0))
		{
			OutFingers.Append(Data.Fingers, 5);
		}
	}
}

void UManusVRAnimInstance::GetRightHandFingers(TArray<float>& OutFingers)
{
	if (_ManusGetData)
	{
		GLOVE_DATA Data;
		if (MANUS_SUCCESS == _ManusGetData(GLOVE_RIGHT, &Data, 0))
		{
			OutFingers.Append(Data.Fingers, 5);
		}
	}
}

FRotator UManusVRAnimInstance::GetLeftHandRotation()
{	
	if (_ManusGetData)
	{
		GLOVE_DATA Data;
		if (MANUS_SUCCESS == _ManusGetData(GLOVE_LEFT, &Data, 0))
		{
			return FRotator(FQuat(Data.Quaternion.x, Data.Quaternion.y, Data.Quaternion.z, Data.Quaternion.w));
		}
	}
	return FRotator(ForceInitToZero);
}

FRotator UManusVRAnimInstance::GetRightHandRotation()
{
	if (_ManusGetData)
	{
		GLOVE_DATA Data;
		if (MANUS_SUCCESS == _ManusGetData(GLOVE_RIGHT, &Data, 0))
		{
			return FRotator(FQuat(Data.Quaternion.x, Data.Quaternion.y, Data.Quaternion.z, Data.Quaternion.w));
		}
	}
	return FRotator(ForceInitToZero);
}

#if (ENGINE_MAJOR_VERSION >= 4) && (ENGINE_MINOR_VERSION >= 11)
bool FManusVRAnimInstanceProxy::Evaluate(FPoseContext& Output)
{
	if (ManusVRAnimInstance == nullptr)
	{
		UE_LOG(LogManusVRAnimation, Warning, TEXT("AnimInstance not initialized"));
		return false;
	}

	return ManusVRAnimInstance->ManusEvaluate(Output);
}

bool UManusVRAnimInstance::ManusEvaluate(struct FPoseContext& Output)
#else
bool UManusVRAnimInstance::NativeEvaluateAnimation(struct FPoseContext& Output)
#endif
{
	if (bUseBlueprint)
		return false;
	
	if (HandAnimation == nullptr)
	{
		if (bIsLeft)
		{
			UE_LOG(LogManusVRAnimation, Warning, TEXT("Animation not set for left glove"));
		}
		else 
		{
			UE_LOG(LogManusVRAnimation, Warning, TEXT("Animation not set for right glove"));
		}	
		return true;
	}

#if (ENGINE_MAJOR_VERSION >= 4) && (ENGINE_MINOR_VERSION >= 11)
	if(Proxy.GetRootNode() != nullptr)
#else
	if (RootNode != nullptr)
#endif
	{
		if (!_ManusGetData)
			return true;

		GLOVE_DATA Data;
		if (MANUS_SUCCESS != _ManusGetData(bIsLeft ? GLOVE_LEFT : GLOVE_RIGHT, &Data, 0))
		{
			Output.ResetToRefPose();
			if (bIsLeft)
			{
				UE_LOG(LogManusVRAnimation, Warning, TEXT("Unable to obtain data from left glove"))
			}
			else
			{
				UE_LOG(LogManusVRAnimation, Warning, TEXT("Unable to obtain data from right glove"))
			}
			return true;
		}

		float AnimationLength = HandAnimation->GetPlayLength();
		for (int32 i = 0; i < 5; i++)
		{
			FCompactPose Pose;
			FBlendedCurve Curve;
			Pose.CopyBonesFrom(Output.Pose);
			Curve.CopyFrom(Output.Curve);
			HandAnimation->GetAnimationPose(Pose, Curve, FAnimExtractContext(Data.Fingers[i] * AnimationLength));
			FQuat PalmRotation(-Data.Quaternion.x, Data.Quaternion.y, Data.Quaternion.z, -Data.Quaternion.w);
			auto BoneContainer = Output.Pose.GetBoneContainer();
			FCompactPoseBoneIndex CompactPoseBoneIndex(0);

			if (bIsLeft)
				CompactPoseBoneIndex = FCompactPoseBoneIndex(BoneContainer.GetPoseBoneIndexForBoneName("Leapmotion_Basehand_Rig_Left"));
			else
				CompactPoseBoneIndex = FCompactPoseBoneIndex(BoneContainer.GetPoseBoneIndexForBoneName("Leapmotion_Basehand_Rig_Right"));

			if (CompactPoseBoneIndex.GetInt() == -1)
			{
				UE_LOG(LogManusVRAnimation, Warning, TEXT("Cannot find root bone. Possible left/right hand animation mismatch?"));
				Output.ResetToRefPose();
				return true;
			}

			Output.Pose[CompactPoseBoneIndex].SetRotation(PalmRotation * FQuat(-1, 1, -1, 1));

			if (BoneContainer.IsValid())
			{
				char BoneName[] = "finger_00";
				BoneName[7] = '0' + i;
				for (int32 j = 0; j < 4; j++)
				{
					BoneName[8] = '0' + j;
					FCompactPoseBoneIndex CompactPoseBoneIndexFinger(BoneContainer.GetPoseBoneIndexForBoneName(BoneName));
					if (CompactPoseBoneIndexFinger.GetInt() == -1)
					{
						UE_LOG(LogManusVRAnimation, Warning, TEXT("Cannot find bone. Possible incorrect animation?"));
						Output.ResetToRefPose();
						return true;
					}
					Output.Pose[CompactPoseBoneIndexFinger].SetRotation(Pose[CompactPoseBoneIndexFinger].GetRotation());
				}
			}
		}
	}
	else
	{
		Output.ResetToRefPose();
		UE_LOG(LogManusVRAnimation, Warning, TEXT("RootNode==NULL"));
		return true;
	}

	return true;
}
