#pragma once

#include "Core.Core.hpp"

#include "Core/Timer.h"
#include "Core/Plugin/PluginServiceRegistry.hpp"

namespace Eclipse::Core
{
	class CORE_API EngineContext
	{
	public:
		Core::Timer& Time;

		Core::PluginServiceRegistry services;
	};
}