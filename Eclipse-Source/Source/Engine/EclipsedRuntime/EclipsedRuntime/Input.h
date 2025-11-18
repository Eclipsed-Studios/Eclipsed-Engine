#pragma once

#include "Runtime_Defines.h"
#include "EclipsedRuntime/Keycodes.h"


class ECL_RUNTIME_API Input
{
public:
	bool GetKeyDown(Keycode keycode);
	bool GetKey(Keycode keycode);
};

ECL_RUNTIME_API Input& GetInput();