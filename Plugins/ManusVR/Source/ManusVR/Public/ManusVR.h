// Some copyright should be here...



#pragma once


#include "ManusVRPrivatePCH.h"

DECLARE_LOG_CATEGORY_EXTERN(LogManusVR, All, All);



class FManusVRModule : public IModuleInterface, public IModularFeature
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};