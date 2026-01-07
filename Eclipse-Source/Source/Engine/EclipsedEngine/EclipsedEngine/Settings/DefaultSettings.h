#pragma once

#include "CoreEngine/Math/Vector/Vector2.h"

namespace Eclipse::Settings
{
	namespace Engine
	{
		const inline char* EngineName = "Eclipsed Engine";
		const inline char* EngineVersion = "0.1.0";
	}

	namespace Default
	{
		namespace Graphics
		{
			const inline bool Fullscreen = false;
			const inline Math::Vector2i Resolution = { 1280, 720 };
		}

		namespace Editor
		{

		}

		namespace User
		{

		}
	}
}