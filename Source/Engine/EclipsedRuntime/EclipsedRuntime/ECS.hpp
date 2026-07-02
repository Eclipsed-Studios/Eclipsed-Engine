#pragma once

#include "defines.h"

// Non templatized methods for ECS.
namespace ECS {
	ECLIPSED_RUNTIME_API void* AddComponentByName(unsigned id, const char* componentName);
};