#include "HierarchyWindow.h"

#include "ImGui/imgui.h"
#include "ECS/ComponentManager.h"
#include "Components/Transform2D.h"

#include "Input/Input.h"

namespace Eclipse::Editor
{
	void HierarchyWindow::Update()
	{
        if (ImGui::BeginPopupContextWindow("##CTX_MENU_RIGHT_CLICK", ImGuiPopupFlags_MouseButtonRight))
        {
			if (ImGui::BeginMenu("Create new..."))
			{
				if (ImGui::MenuItem("GameObject")) 
				{ 
					// TODO: Fix a gameobject creation manager
					static int id = 1000;
					ComponentManager::AddComponent<Transform2D>(id++);
				}

				ImGui::EndMenu();
			}

            ImGui::EndPopup();
        }


		for (const auto& [id, data] : ComponentManager::myEntityIdToEntityData)
		{
			if (ImGui::Button(std::string(data.name + "##" + std::to_string(id)).c_str()))
			{
				CurrentGameObjectID = id;
			}
		}
	}
}