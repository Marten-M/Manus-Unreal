// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
// Copyright 2015 Manus Machina

#pragma once
#include "ManusLib.h"
#include "Runtime/Launch/Resources/Version.h"
#if (ENGINE_MAJOR_VERSION >= 4) && (ENGINE_MINOR_VERSION >= 11)
#include "Animation/AnimInstanceProxy.h"
#endif
#include "ManusVRAnimInstance.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogManusVRAnimation, All, All);


#if (ENGINE_MAJOR_VERSION >= 4) && (ENGINE_MINOR_VERSION >= 11)
class UManusVRAnimInstance;

struct FManusVRAnimInstanceProxy : public FAnimInstanceProxy
{
	FManusVRAnimInstanceProxy() : FAnimInstanceProxy(), ManusVRAnimInstance(nullptr) {}
	FManusVRAnimInstanceProxy(UAnimInstance* Instance) : FAnimInstanceProxy(Instance), ManusVRAnimInstance(nullptr) {}

	virtual bool Evaluate(FPoseContext& Output) override;

	UManusVRAnimInstance*	ManusVRAnimInstance;
};
#endif


UCLASS(Blueprintable, BlueprintType)
class UManusVRAnimInstance : public UAnimInstance
{
	GENERATED_UCLASS_BODY()

#if (ENGINE_MAJOR_VERSION >= 4) && (ENGINE_MINOR_VERSION >= 11)
	bool ManusEvaluate(struct FPoseContext& Output);
#else
		bool NativeEvaluateAnimation(struct FPoseContext& Output) override;
#endif

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


#if (ENGINE_MAJOR_VERSION >= 4) && (ENGINE_MINOR_VERSION >= 11)
private:
	UPROPERTY(Transient, BlueprintReadOnly, Category = ManusVR, meta = (AllowPrivateAccess = "true"))
		FManusVRAnimInstanceProxy Proxy;

	virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override { return& Proxy; }
	virtual void DestroyAnimInstanceProxy(FAnimInstanceProxy* InProxy) override {}
	friend struct FManusVRAnimInstanceProxy;
#endif
};
