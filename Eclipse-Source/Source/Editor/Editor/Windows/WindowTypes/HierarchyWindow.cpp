#ifdef ECLIPSED_EDITOR
#include "HierarchyWindow.h"

#include "ImGui/imgui.h"
#include "CoreEngine/ECS/ComponentManager.h"
#include "CoreEngine/Components/Transform2D.h"
#include "CoreEngine/Components/UI/Canvas.h"
#include "CoreEngine/Components/UI/UIImage.h"
#include "CoreEngine/Components/UI/RectTransform.h"

#include "CoreEngine/Input/Input.h"

#include "CoreEngine/ECS/ECS.hpp"

namespace Eclipse::Editor
{
	void HierarchyWindow::HierarchyButton(GameObject* aGameObject, GameObjectID aGOID)
	{
		GameObject* parent = data->GetParent();
		if (parent)
			return;
		
		if (ImGui::Button(std::string(data->GetName() + "##" + std::to_string(id)).c_str()))
		{
			CurrentGameObjectID = aGOID;
			InspectorWindow::activeType = ActiveItemTypes_GameObject;
		}
	}

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
				else if (ImGui::MenuItem("Canvas"))
				{
					GameObject* obj = ComponentManager::CreateGameObject();
					obj->AddComponent<Canvas>();

					obj->SetName("Canvas");
				}
				else if (ImGui::MenuItem("Image"))
				{
					GameObject* obj = ComponentManager::CreateGameObjectNoTransform();
					obj->AddComponent<RectTransform>();
					obj->AddComponent<UIImage>();

					obj->SetName("Image");
				}

				ImGui::EndMenu();
			}

			ImGui::EndPopup();
		}


		for (const auto& [id, data] : ComponentManager::myEntityIdToEntity)
		{
			HierarchyButton(data, id);

			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
			{
				ImGui::SetDragDropPayload("DND_Childing_Reordering", &id, sizeof(unsigned));

				ImGui::Text(data->GetName().c_str());
				ImGui::EndDragDropSource();
			}

			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_Childing_Reordering"))
				{
					IM_ASSERT(payload->DataSize == sizeof(unsigned));
					unsigned draggedEntityID = *(const unsigned*)payload->Data;

					auto it = ComponentManager::myEntityIdToEntity.find(draggedEntityID);
					if (it != ComponentManager::myEntityIdToEntity.end())
					{
						GameObject* targetGO = it->second;
						targetGO->SetParent(data);
					}
				}
				ImGui::EndDragDropTarget();
			}
		}
	}
}
#endif