#pragma once

#include "Runtime_Defines.h"

class ECL_RUNTIME_API Time
{
public:
	float GetDeltaTime();
	float GetTotalTime();
};

ECL_RUNTIME_API Time& GetTimer();