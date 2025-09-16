#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace Eclipse 
{ 
	class Component;
}

namespace Eclipse::Reflection
{
	class AbstractSerializedVariable;
	class ReflectionManager
	{
	private:
		using VariableList = std::vector<AbstractSerializedVariable*>;
		using CompToTypeList = std::unordered_map<Component*, VariableList>;

		static inline CompToTypeList registeredVariables;

	public:
		static void RegisterVariable(AbstractSerializedVariable* ptr);
		static void UnregisterVariable(AbstractSerializedVariable* ptr);
		static void DrawInspector(Component* aComp);

		static CompToTypeList& GetList();
	};
}