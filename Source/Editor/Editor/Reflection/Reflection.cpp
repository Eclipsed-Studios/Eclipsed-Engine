#include "Reflection.h"

#include "ImGui/imgui.h"

#include "ReflectedVariable.h"
#include "Components/Base/Component.h"

namespace Eclipse
{
	void Reflection::RegisterVariable(AbstractReflectedVariable* ptr)
	{
		TypeToList& compIdToList = registeredVariables[ptr->pComponent];
		VariableList& list = compIdToList[ptr->myTypeName];

		list.push_back(ptr);
	}

	void Reflection::UnregisterVariable(AbstractReflectedVariable* ptr)
	{
		if (registeredVariables.find(ptr->pComponent) == registeredVariables.end()) return;
		TypeToList& compIdToList = registeredVariables[ptr->pComponent];

		if (compIdToList.find(ptr->myTypeName) == compIdToList.end()) return;
		VariableList& list = compIdToList[ptr->myTypeName];

		if (list.empty()) return;

		list.erase(
			std::remove_if(list.begin(), list.end(),
				[&](const auto& element) {
					return element->myID == ptr->myID;
				}),
			list.end());



		if (list.empty()) {
			compIdToList.erase(ptr->myTypeName);

			bool hasVariables = false;
			for (auto it = compIdToList.begin(); it != compIdToList.end();)
			{
				auto& list = it->second;

				if (list.empty())
				{
					it = compIdToList.erase(it);
				}
				else
				{
					hasVariables = true;
					++it;
				}
			}


			if (!hasVariables)
			{
				registeredVariables.erase(ptr->pComponent);
			}
		}
	}

	void Reflection::DrawInspector(Component* aComponent)
	{
		TypeToList& typeList = registeredVariables[aComponent];

		for (auto& [type, list] : typeList)
		{
			for (auto& element : list)
			{
				element->DrawInspector();
			}
		}
	}
}