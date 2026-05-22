#include "ComponentInspectorDrawer.h"

#include "ImGui/imgui.h"

namespace Eclipse::Editor
{
	static void DefaultDraw(void* comp)
	{
		ImGui::Text("No drawer.");
	}

	std::unordered_map<std::string, InspectorDrawFn> ComponentInspectorRegistry::registry;

	void ComponentInspectorRegistry::Register(std::string name, InspectorDrawFn fn)
	{
		registry[name] = fn;
	}

	InspectorDrawFn ComponentInspectorRegistry::GetDrawFunction(std::string name)
	{
		auto it = registry.find(name);
		if(it != registry.end())
			return it->second;

		return DefaultDraw;
	}
}