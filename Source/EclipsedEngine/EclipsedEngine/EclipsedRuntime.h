#pragma once

#include "Core/Engine.h"
#include "EclipsedEngine.Core.hpp"

#include <thread>

#include "Physics/PhysicsEngine.h"
#include "ECS/ComponentManager.h"

namespace Eclipse
{
	class ECL_API EclipsedRuntime
	{
	public:
#ifdef ECL_EDITOR
		void StartEngine(const std::string& path);
#else
		void StartEngine();
#endif

		void LateStart();

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
