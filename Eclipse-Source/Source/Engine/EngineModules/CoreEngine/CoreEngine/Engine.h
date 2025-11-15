#pragma once

#include "Game/../pch.h"

namespace Eclipse
{
	class Engine
	{
	public:
		void Init();
		
		void BeginFrame();
		void Update();
		void Render();
		void EndFrame();
	};
}