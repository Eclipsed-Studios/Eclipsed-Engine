#pragma once

#include "CoreEngine/Engine.h"
#include "Runtime_Defines.h"

namespace Eclipse
{
	class ECL_RUNTIME_API EclipsedRuntime
	{
	public:
		void StartEngine(const std::string& path);

		void UpdateGame();

		void Render();

		void Update();
		void EndFrame();
		bool BeginFrame();

	private:
		Engine engine;
	};
}
