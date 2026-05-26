#pragma once

#include "CoreEngine/Macros/defines.h"

namespace Eclipse
{
	class ECLIPSED_API Timer 
	{
	public:
		static void SetTimeScale(float timeScale);

		static float GetDeltaTime();
		static float GetTotalTime();
		static float GetTimeScale();
	};
}