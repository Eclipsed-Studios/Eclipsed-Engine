#pragma once

#include "Timer.h"
#include "Core.Core.hpp"

namespace Eclipse
{
	class CORE_API Engine
	{
	public:
		void Init();
		
		void Update();
		void End();
	};
}