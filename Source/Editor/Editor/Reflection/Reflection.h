#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "Random.h"

#include "ImGui/ImGui/imgui.h"



namespace Eclipse
{
	class Component;
	class AbstractReflectedVariable;
	class Reflection
	{
	public:
		static void RegisterVariable(AbstractReflectedVariable* ptr);
		static void UnregisterVariable(AbstractReflectedVariable* ptr);
		static void DrawInspector(Component* aComponent);

	private:
		using VariableList = std::vector<AbstractReflectedVariable*>;
		using TypeToList = std::unordered_map<std::string, VariableList>;
		using CompToTypeList = std::unordered_map<Component*, TypeToList>;

		static inline CompToTypeList registeredVariables;
	};
}