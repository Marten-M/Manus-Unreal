// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
// Copyright 2015 Manus Machina

#pragma once
#include "ManusLib.h"
#include "ManusVRAnimInstance.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogManusVRAnimation, All, All);

UCLASS(Blueprintable, BlueprintType)
class UManusVRAnimInstance : public UAnimInstance
{
	GENERATED_UCLASS_BODY()

		bool NativeEvaluateAnimation(struct FPoseContext& Output) override;

	// Animation to use
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ManusVR)
		UAnimSequence* HandAnimation;

	// Left or right hand
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ManusVR)
		bool bIsLeft;

	// Use Blueprint glove processing or build-in
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ManusVR)
		bool bUseBlueprint = false;

	UFUNCTION(BlueprintCallable, Category = ManusVR)
		FRotator GetLeftHandRotation();

	UFUNCTION(BlueprintCallable, Category = ManusVR)
		FRotator GetRightHandRotation();

	UFUNCTION(BlueprintCallable, Category = ManusVR)
		void GetRightHandFingers(TArray<float>& OutFingers);

	UFUNCTION(BlueprintCallable, Category = ManusVR)
		void GetLeftHandFingers(TArray<float>& OutFingers);

};
