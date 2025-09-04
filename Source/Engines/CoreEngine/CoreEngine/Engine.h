#pragma once

#include "Game.h"

namespace ENGINE_NAMESPACE
{
	class Engine
	{
	public:
		Engine() = delete;
		~Engine() = delete;

	public:
		static void Init();
		
		static bool BeginFrame();
		static void Update();
		static void EndFrame();
		static void End();

		static inline Game game;
	};
}