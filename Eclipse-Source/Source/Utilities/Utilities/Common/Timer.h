#pragma once

#include <chrono>

namespace Eclipse
{
    class Time
    {
    public:
         void Init();
         void Update();

         void SetTimeScale(float timeScale);

         float GetDeltaTime();
         float GetTotalTime();

    private:
        std::chrono::high_resolution_clock::time_point startTime;
        std::chrono::high_resolution_clock clock;
        std::chrono::duration<float> duration;

        float myDeltaTime = 0;
        float myTotalTime = 0;
        float myTimeScale = 1;
    };
}