#include "WindowRegistry.h"
#include "ComponentRegistry.h"

namespace ENGINE_NAMESPACE::Editor
{
	void ComponentRegistry::RegisterComponent(const std::string& name, std::function<void(int)> addComponentMethod)
	{
		components[name] = addComponentMethod;
	}

	void ComponentRegistry::AddComponent(const std::string& name, int id)
	{
		components[name](id);
	}

	const std::unordered_map<std::string, std::function<void(int)>>& ComponentRegistry::GetComponents()
	{
		return components;
	}
}