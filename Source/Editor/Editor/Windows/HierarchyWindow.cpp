#include "HierarchyWindow.h"

#include "ImGui/imgui.h"
#include "ECS/ComponentManager.h"


namespace ENGINE_NAMESPACE::Editor
{
	void HierarchyWindow::Update()
	{
		for (const auto& [id, data] : ComponentManager::myEntityIdToEntityData)
		{
			if (ImGui::Button(std::string(data.name + "##" + std::to_string(id)).c_str()))
			{
				CurrentGameObjectID = id;
			}
		}
	}
}