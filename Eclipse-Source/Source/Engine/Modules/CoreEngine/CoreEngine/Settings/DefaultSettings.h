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
			const inline int NumberOfRenderBuffers = 0;
			const inline Math::Vector2f Resolution = { 1280, 720 };
		}

		namespace Engine
		{

		}

		namespace Editor
		{

		}

		namespace User // Game related
		{

		}

		namespace Build
		{

		}

		namespace Network
		{

		}

		namespace Physics
		{
			const inline Math::Vector2f Gravity = { 0.f, -9.82f};

		}
	}
}