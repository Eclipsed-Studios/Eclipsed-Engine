#include "ECS.hpp"

#include "EclipsedEngine/Reflection/Registry/ComponentRegistry.h"
#include "EntityEngine/ComponentManager.h"

void* ECS::AddComponentByName(unsigned id, const char* componentName)
{
	auto func = Eclipse::ComponentRegistry::GetAddComponentByRttiTypeName(componentName);
	return func(id);
	//return nullptr;
}
