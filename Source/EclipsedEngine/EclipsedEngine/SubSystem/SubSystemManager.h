#pragma once

#include "EclipsedEngine.Core.hpp"
#include "SubSystem.h"
#include <vector>

namespace Eclipse
{
	class ECL_API SubSystemManager {
	public:
		static void RegisterSystem(void* aSubSystem);

	public:
		static void InitSystems();
		static void ExecuteSystems();

		static std::vector<SubSystem*> myRegisteredSystems;
	};
}