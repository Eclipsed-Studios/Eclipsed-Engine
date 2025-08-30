#pragma once

#include <chrono>

namespace ENGINE_NAMESPACE
{
    class Time
    {
    public:
        static void Init();
        static void Update();

        static void SetTimeScale();

        static float GetDeltaTime() { return myDeltaTime; }
        static float GetTotalTime() { return myTotalTime; }

    private:
        static inline std::chrono::high_resolution_clock::time_point startTime;
        static inline std::chrono::high_resolution_clock clock;
        static inline std::chrono::duration<float> duration;

        static inline float myDeltaTime = 0;
        static inline float myTotalTime = 0;
        static inline float myTimeScale = 1;
    };

    inline void Time::Init()
    {
        startTime = clock.now();
    }

    inline void Time::Update()
    {
        duration = clock.now() - startTime;
        float newTotalTime = duration.count();
        float deltaTimeNoScaled = newTotalTime - myTotalTime;
        myDeltaTime = deltaTimeNoScaled * myTimeScale;
        myTotalTime = newTotalTime;
    }
}