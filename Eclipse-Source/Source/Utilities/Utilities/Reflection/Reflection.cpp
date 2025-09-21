#include "Reflection.h"

#include "ImGui/ImGui/imgui.h"

#include "Random.h"

#include "ImGui/ImGui/imgui.h"
#include "SerializedVariable.h"

namespace Eclipse::Reflection
{
	void ReflectionManager::RegisterVariable(AbstractSerializedVariable* ptr)
	{
		VariableList& list = registeredVariables[ptr->pComponent];
		list.push_back(ptr);
	}

	void ReflectionManager::UnregisterVariable(AbstractSerializedVariable* ptr)
	{
		//if (registeredVariables.find(ptr->pComponent) == registeredVariables.end()) return;
		//TypeToList& compIdToList = registeredVariables[ptr->pComponent];

		//if (compIdToList.find(ptr->myTypeName) == compIdToList.end()) return;
		//VariableList& list = compIdToList[ptr->myTypeName];

		//if (list.empty()) return;

		//list.erase(
		//	std::remove_if(list.begin(), list.end(),
		//		[&](const auto& element) {
		//			return element->pComponent == ptr->pComponent;
		//		}),
		//	list.end());



		//if (list.empty()) {
		//	compIdToList.erase(ptr->myTypeName);

		//	bool hasVariables = false;
		//	for (auto it = compIdToList.begin(); it != compIdToList.end();)
		//	{
		//		auto& list = it->second;

		//		if (list.empty())
		//		{
		//			it = compIdToList.erase(it);
		//		}
		//		else
		//		{
		//			hasVariables = true;
		//			++it;
		//		}
		//	}


		//	if (!hasVariables)
		//	{
		//		registeredVariables.erase(ptr->pComponent);
		//	}
		//}
	}

	void ReflectionManager::DrawInspector(Component* aComp, const char* name)
	{
		VariableList& list = registeredVariables[aComp];

		for (auto& element : list)
		{
			element->DrawInspector();
		}
	}

	ReflectionManager::CompToTypeList& ReflectionManager::GetList()
	{
		return registeredVariables;
	}
}