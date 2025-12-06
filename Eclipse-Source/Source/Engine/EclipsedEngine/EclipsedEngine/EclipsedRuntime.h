#pragma once

#include "CoreEngine/Engine.h"

namespace Eclipse
{
	class EclipsedRuntime
	{
	public:
		void StartEngine(const std::string& path);

		void UpdateGame();

		void Render();

		void Update();
		void Shutdown();
		void EndFrame();
		bool BeginFrame();

	private:
		Engine engine;
	};
}
