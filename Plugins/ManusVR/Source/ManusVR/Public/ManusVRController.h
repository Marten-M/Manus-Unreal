#pragma once
#include "ManusVRController.generated.h"
//#include "ManusVRPrivatePCH.h"
//#include "EnginePrivate.h"
DECLARE_LOG_CATEGORY_EXTERN(LogManusVRController, All, All);



// error messages tell the .generated.h file should be the last include
// while documentation tells it should be the first.



//Input Mapping Keys
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
	//~UManusVRController();
	//virtual void OnRegister() override;
	//virtual void OnUnregister() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

};