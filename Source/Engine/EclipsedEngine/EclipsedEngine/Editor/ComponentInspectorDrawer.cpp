#ifdef ECLIPSED_EDITOR

#include "ComponentInspectorDrawer.h"

#include "ImGui/imgui.h"

namespace Eclipse::Editor
{
	static void DefaultDraw(void* comp)
	{
		ImGui::Text("No drawer.");
	}

	std::unordered_map<std::string, InspectorDrawFn>& ComponentInspectorRegistry::Registry()
	{
		static std::unordered_map<std::string, InspectorDrawFn> registry;
		return registry;
	}

	void ComponentInspectorRegistry::Register(std::string name, InspectorDrawFn fn)
	{
		Registry()[name] = fn;
	}

	InspectorDrawFn ComponentInspectorRegistry::GetDrawFunction(std::string name)
	{
		std::unordered_map<std::string, InspectorDrawFn>& registry = Registry();

		auto it = registry.find(name);
		if(it != registry.end())
			return it->second;

		return DefaultDraw;
	}
}

#endif