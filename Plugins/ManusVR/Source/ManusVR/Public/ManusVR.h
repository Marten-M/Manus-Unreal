// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
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