#include "pch.h"  

#include "Timer.h"
#include <chrono>

namespace Eclipse
{
	Time::Time()
	{
		time = this;
	}

	Time& Time::Get()
	{
		return *time;
	}

	Time* Time::time = nullptr;

	void Time::Init()
	{
		startTime = clock.now();
	}

	void Time::Update()
	{
		CORE_PROFILE_SCOPED;
		duration = clock.now() - startTime;
		float newTotalTime = duration.count();
		float deltaTimeNoScaled = newTotalTime - myTotalTime;
		myDeltaTime = deltaTimeNoScaled * myTimeScale;
		myTotalTime = newTotalTime;
	}

	void Time::SetTimeScale(float timeScale)
	{
		myTimeScale = timeScale;
	}

	float Time::GetDeltaTime()
	{
		return myDeltaTime * myTimeScale;
	}

	float Time::GetTimeScale()
	{
		return myTimeScale;
	}

	float Time::GetTotalTime()
	{
		return myTotalTime;
	}
}