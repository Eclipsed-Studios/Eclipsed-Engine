#pragma once

#include "Window.h"

namespace ENGINE_NAMESPACE::Editor
{
	class DebugWindow final : public AbstractWindow 
	{
		BASE_WINDOW(DebugWindow, "Debug")
	};
}