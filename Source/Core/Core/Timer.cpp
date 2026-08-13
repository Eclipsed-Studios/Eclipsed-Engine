#include "pch.h"  

#include "Timer.h"
#include <chrono>

namespace Eclipse::Core
{
    Timer::Timer() : duration(0)
    {
        Init();
    }

    void Timer::Init()
    {
        startTime = clock.now();
    }

    void Timer::Update()
    {
        duration = clock.now() - startTime;
        float newTotalTime = duration.count();
        float deltaTimeNoScaled = newTotalTime - myTotalTime;
        myDeltaTime = deltaTimeNoScaled * myTimeScale;
        myTotalTime = newTotalTime;
    }

    void Timer::SetTimeScale(float timeScale)
    {
        myTimeScale = timeScale;
    }

    float Timer::GetDeltaTime()
    {
        return myDeltaTime * myTimeScale;
    }

    float Timer::GetTimeScale()
    {
        return myTimeScale;
    }

    float Timer::GetTotalTime()
    {
        return myTotalTime;
    }
}