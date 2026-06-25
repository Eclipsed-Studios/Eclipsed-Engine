#pragma once

#include "EclipsedEngine/Editor/Windows/WindowBase.h"
#include "Logger/DebugLogger.h"

//#include ""

namespace Eclipse::Editor
{
	class ProfilerWindow final : public AbstractWindow 
	{
		EDITOR_WINDOW_BASE_2(ProfilerWindow, "Performance Profiler")

	public:
		void Update() override;
	};
}