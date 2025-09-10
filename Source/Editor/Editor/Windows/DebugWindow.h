#pragma once

#include "WindowBase.h"

namespace ENGINE_NAMESPACE::Editor
{
	class DebugWindow final : public AbstractWindow 
	{
		BASE_SELECTION(DebugWindow, "Debug")
	};
}