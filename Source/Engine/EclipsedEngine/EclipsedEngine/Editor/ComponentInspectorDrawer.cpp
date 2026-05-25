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

	bool ComponentInspectorRegistry::InspectorExists(const std::string& name)
	{
		std::unordered_map<std::string, InspectorDrawFn>& registry = Registry();
		auto it = registry.find(name);

		return it != registry.end();
	}

	void ComponentInspectorRegistry::RegisterInspector(const std::string& name, InspectorDrawFn fn)
	{
		std::unordered_map<std::string, InspectorDrawFn>& registry = Registry();
		registry[name] = fn;
	}

	InspectorDrawFn ComponentInspectorRegistry::GetDrawFunction(const std::string& name)
	{
		std::unordered_map<std::string, InspectorDrawFn>& registry = Registry();

		auto it = registry.find(name);
		if(it != registry.end())
			return it->second;

		return DefaultDraw;
	}
}

#endif