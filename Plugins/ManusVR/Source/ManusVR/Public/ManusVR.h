// Copyright 2015 Manus Machina

#pragma once
#include "ManusVRPrivatePCH.h"

DECLARE_LOG_CATEGORY_EXTERN(LogManusVR, All, All);

class FManusVRModule : public IModuleInterface, public IModularFeature
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};