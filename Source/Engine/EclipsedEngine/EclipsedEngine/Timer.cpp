#include "pch.h"  

#include "Timer.h"
#include "CoreEngine/Timer.h"

namespace Eclipse
{
	void Timer::SetTimeScale(float timeScale)
	{
		Time::SetTimeScale(timeScale);
	}
	
	float Timer::GetDeltaTime()
	{
		return Time::GetDeltaTime();
	}
	float Timer::GetTotalTime()
	{
		return Time::GetTotalTime();
	}
	float Timer::GetTimeScale()
	{
		return Time::GetTimeScale();
	}
}