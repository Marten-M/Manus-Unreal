// Copyright 2015 Manus VR

#pragma once
#include "Manus.h"

// ManusInit, ManusExit
typedef int(*int_void)();
// ManusGetData
typedef int(*int_hand_pdata_uint)(GLOVE_HAND hand, GLOVE_DATA* data, unsigned int timeout);

extern int_void _ManusInit;
extern int_void _ManusExit;
extern int_hand_pdata_uint _ManusGetData;

#if _WIN32
#define PlatformString "Win32"
#endif

#if _WIN64
#define PlatformString "Win64"
#endif
