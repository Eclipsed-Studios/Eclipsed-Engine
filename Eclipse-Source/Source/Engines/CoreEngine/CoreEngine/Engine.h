#pragma once

#include "Game.h"

namespace Eclipse
{
	class Engine
	{
	public:
		Engine() = delete;
		~Engine() = delete;

	public:
		static void Init();
		
		static void Internal_Update();

		static bool BeginFrame();
		static void Update();
		static void EndFrame();

	private:
		static void InitSubSystems();
	};
}