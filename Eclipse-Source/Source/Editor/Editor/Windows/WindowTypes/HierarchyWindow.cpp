#ifdef ECLIPSED_EDITOR
#include "HierarchyWindow.h"

#include "ImGui/imgui.h"
#include "ECS/ComponentManager.h"
#include "Components/Transform2D.h"

#include "Input/Input.h"

#include "ECS/ECS.hpp"

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
					GameObject* obj = CreateGameObject();
					obj->SetName("New GameObject");
				}

				ImGui::EndMenu();
			}

            ImGui::EndPopup();
        }


		for (const auto& [id, data] : ComponentManager::myEntityIdToEntity)
		{
			if (ImGui::Button(std::string(data->GetName() + "##" + std::to_string(id)).c_str()))
			{
				CurrentGameObjectID = id;
				InspectorWindow::activeType = ActiveItemTypes_GameObject;
			}
		}
	}
}
#endif