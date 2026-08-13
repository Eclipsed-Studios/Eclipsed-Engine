#pragma once

#include <chrono>

#include "Core.Core.hpp"

namespace Eclipse::Core
{
	class CORE_API Timer
	{
	public:
		Timer();
		~Timer() = default;

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

		float myDeltaTime;
		float myTotalTime;
		float myTimeScale;
	};
}