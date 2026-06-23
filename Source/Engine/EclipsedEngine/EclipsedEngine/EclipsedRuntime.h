#pragma once

#include "CoreEngine/Input/Input.h"
#include "CoreEngine/Timer.h"
#include "CoreEngine/Macros/defines.h"

#include <thread>

#include "PhysicsEngine/PhysicsEngine.h"
#include "EntityEngine/ComponentManager.h"

#include "Reflection/ClassRegistry.h"

namespace Eclipse
{
	class ECLIPSED_API EclipsedRuntime
	{
	public:
		static EclipsedRuntime& Get();

		EclipsedRuntime();

	public:
#ifdef ECLIPSED_EDITOR
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

	public:
		Input& GetInput();
		Time& GetTime();
		ClassRegistry& GetClassReg();

	private:
		PhysicsEngine physicsEngine;
		ComponentManager componentManager;
		Input input;
		Time time;
		static inline ClassRegistry clsReg;

		static EclipsedRuntime* runtime;
	};
}
