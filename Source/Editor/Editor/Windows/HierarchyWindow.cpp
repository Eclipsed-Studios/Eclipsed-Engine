#include "HierarchyWindow.h"

#include "ImGui/imgui.h"
#include "ECS/ComponentManager.h"


namespace ENGINE_NAMESPACE::Editor
{
	HierarchyWindow::HierarchyWindow(const int& aId)
	{
		myWindowName = "Hierarchy";
		myID = aId == -1 ? Random::GetValue<int>() : aId;
	}

	void HierarchyWindow::Open()
	{
	}
	
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
	
	void HierarchyWindow::Close()
	{
	}
}