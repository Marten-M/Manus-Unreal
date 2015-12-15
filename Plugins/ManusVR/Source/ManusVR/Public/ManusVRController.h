// Copyright 2015 Manus Machina

#pragma once
#include "ManusVRController.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogManusVRController, All, All);

struct EManus
{
	static const FKey Left_Palm;
	static const FKey Left_Thumb;
	static const FKey Left_Index;
	static const FKey Left_Middle;
	static const FKey Left_Ring;
	static const FKey Left_Pinky;

	static const FKey Right_Palm;
	static const FKey Right_Thumb;
	static const FKey Right_Index;
	static const FKey Right_Middle;
	static const FKey Right_Ring;
	static const FKey Right_Pinky;
};


UCLASS(ClassGroup = Input, meta = (BlueprintSpawnableComponent))
class UManusVRController : public UActorComponent
{
	GENERATED_UCLASS_BODY()
public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};