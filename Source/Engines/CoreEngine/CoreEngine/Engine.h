#pragma once

#include "Components/SpriteRendrer2D.h"

namespace ENGINE_NAMESPACE
{
	class Engine
	{
	public:
		Engine() = delete;
		~Engine() = delete;

	public:
		static void Init();
		static void Update();
	};
}