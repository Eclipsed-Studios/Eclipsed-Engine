#pragma once

#include <chrono>

#ifdef ECLIPSED_EDITOR
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

namespace Eclipse
{
	class ENGINE_API Time
	{
	public:
		Time() = delete;
		~Time() = delete;

	public:
		static void Init();
		static void Update();

		static void SetTimeScale(float timeScale);

		static float GetDeltaTime();
		static float GetTotalTime();
		static float GetTimeScale();

	private:
		static std::chrono::high_resolution_clock::time_point startTime;
		static std::chrono::high_resolution_clock clock;
		static std::chrono::duration<float> duration;

		static float myDeltaTime;
		static float myTotalTime;
		static float myTimeScale;
	};
}