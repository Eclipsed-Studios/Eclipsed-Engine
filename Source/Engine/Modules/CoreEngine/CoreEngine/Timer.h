#pragma once

#include <chrono>

namespace Eclipse
{
	class Time
	{
	public:
		Time();

		static Time& Get();

	private:
		static Time* time;

	public:
		void Init();
		void Update();

		void SetTimeScale(float timeScale);

		float GetDeltaTime();
		float GetTotalTime();
		float GetTimeScale();

	private:
		std::chrono::high_resolution_clock::time_point startTime;
		std::chrono::high_resolution_clock clock;
		std::chrono::duration<float> duration;

		float myDeltaTime = 0.f;
		float myTotalTime = 0.f;
		float myTimeScale = 1.f;
	};
}