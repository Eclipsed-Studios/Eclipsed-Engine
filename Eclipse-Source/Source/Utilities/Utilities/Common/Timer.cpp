#pragma once

#include <chrono>

namespace Eclipse
{
    void Time::Init()
    {
        startTime = clock.now();
    }

    void Time::Update()
    {
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

    float Time::GetTotalTime()
    {
        return myTotalTime;
    }
}