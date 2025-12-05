#ifdef ECLIPSED_EDITOR
#include "HierarchyWindow.h"

#include "ImGui/imgui.h"
#include "EntityEngine/ComponentManager.h"
#include "EclipsedEngine/Components/Transform2D.h"
#include "EclipsedEngine/Components/UI/Canvas.h"
#include "EclipsedEngine/Components/UI/UIImage.h"
#include "EclipsedEngine/Components/Rendering/TextRenderer.h"
#include "EclipsedEngine/Components/UI/RectTransform.h"
#include "CoreEngine/Input/Input.h"
#include "EntityEngine/ECS.hpp"
#include "EntityEngine/GameObject.h"

#include "CoreEngine/Clipboard.h"
#include "EclipsedEngine/Scenes/SceneLoader.h"
#include "EclipsedEngine/Editor/EditorUIManager.h"

#include "Font-Awesome/7/IconsFontAwesome7.h"

namespace Eclipse::Editor
{
	void HierarchyWindow::HierarchyButton(GameObject* aGameObject, float totalIndent)
	{
		unsigned id = aGameObject->GetID();
		bool goIsOpen = gameobjectIdsThatAreOpen.find(id) != gameobjectIdsThatAreOpen.end();

		ImGui::PushFont(Editor::EditorUIManager::FontExtraSmall);
		if (aGameObject->GetChildCount() > 0)
		{
			float cursorXpos = ImGui::GetCursorPosX() + totalIndent;

			ImGui::SetCursorPosX(cursorXpos - 2);

			if (goIsOpen)
			{
				ImGui::Text(ICON_FA_SORT_DOWN);
				ImGui::SameLine();
			}
			else
			{
				ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 4);
				ImGui::Text(ICON_FA_PLAY);
				ImGui::SameLine();
				ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 4);
			}

			ImGui::SetCursorPosX(cursorXpos - 6);
			if (ImGui::InvisibleButton(std::string("##InvisibleButtonForChilding" + std::to_string(id)).c_str(), ImVec2(20, 20)))
			{
				if (gameobjectIdsThatAreOpen.find(id) != gameobjectIdsThatAreOpen.end())
					gameobjectIdsThatAreOpen.erase(id);
				else
					gameobjectIdsThatAreOpen.emplace(id);
			}
			ImGui::SameLine();
		}

		if (!goIsOpen && aGameObject->GetChildCount() > 0)
		{
			ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 4);
		}

		if (id == CurrentGameObjectID)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_ButtonHovered));
		}

		ImGui::SetCursorPosX(totalIndent + 24);
		std::string itemName = std::string(aGameObject->GetName() + "##" + std::to_string(id));
		ImVec2 textSize = ImGui::CalcTextSize(itemName.c_str());
		bool clickedButton = ImGui::Button(itemName.c_str(), ImVec2(textSize.x, 20));

		if (id == CurrentGameObjectID)
			clickedButton = false;

		if (clickedButton)
		{
			CurrentGameObjectID = id;
			InspectorWindow::SetActiveType(ActiveItemTypes_GameObject);
		}
		ImGui::PopFont();
		if (id == CurrentGameObjectID && !clickedButton)
		{
			ImGui::PopStyleColor();
		}

		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
		{
			ImGui::SetDragDropPayload("DND_Childing_Reordering", &id, sizeof(unsigned));

			ImGui::Text(aGameObject->GetName().c_str());
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
					AssignParentChildren(it->second, aGameObject);
				}
			}
			ImGui::EndDragDropTarget();
		}

		if (gameobjectIdsThatAreOpen.find(id) != gameobjectIdsThatAreOpen.end())
		{
			std::vector<GameObject*> children = aGameObject->GetChildren();
			totalIndent += 24.f;

			for (auto& child : children)
			{
				HierarchyButton(child, totalIndent);
			}
		}
	}

	bool IsNewParentMyChild(Eclipse::GameObject* aParent, Eclipse::GameObject* aChild)
	{
		auto& children = aChild->GetChildren();
		for (auto& child : children)
		{
			if (child->GetID() == aParent->GetID())
				return true;

			if (IsNewParentMyChild(aParent, child))
				return true;
		}

		return false;
	}

	bool HierarchyWindow::CheckCopomentType(GameObject* aChild, GameObject* aParent)
	{
		if (aParent->GetComponent<Transform2D>() && aChild->transform)
		{
			/* code */
		}

		return true;
	}

	void HierarchyWindow::AssignParentChildren(GameObject* aChild, GameObject* aParent)
	{
		if (IsNewParentMyChild(aParent, aChild))
			return;

		auto& oldParent = aChild->GetParent();
		if (auto& parent = oldParent)
		{
			if (oldParent->GetID() == aParent->GetID())
				return;

			auto& children = parent->GetChildren();
			size_t childIndex = aChild->GetChildIndex();

			for (int i = childIndex; i < children.size() - 1; i++)
			{
				children[i] = children[i + 1];
				children[i]->SetChildIndex(i);
			}

			children.pop_back();
			if (children.size() <= 0)
			{
				gameobjectIdsThatAreOpen.erase(parent->GetID());
			}
		}

		if (aChild->transform && aParent->transform)
		{
			Math::Vector2f childPos = aChild->transform->GetPosition();
			Math::Vector3f positionVec3(childPos.x, childPos.y, 1);
			positionVec3 = positionVec3 * aParent->transform->GetTransformMatrix().GetInverse();
			childPos = { positionVec3.x, positionVec3.y };
			aChild->transform->SetPosition(childPos);
		}

		if (auto* recttransform = aChild->GetComponent<RectTransform>())
		{
			if (recttransform->myCanvas = aParent->GetComponent<Canvas>())
			{
				recttransform->myCanvas->canvasCameraTransform.PositionOffset = { 0.f, 0.f };
				recttransform->myCanvas->canvasCameraTransform.Rotation = 0.f;
				recttransform->myCanvas->canvasCameraTransform.ScaleMultiplier = { 1.f, 1.f };
			}
		}


		aChild->SetParent(aParent);
		aParent->AddChild(aChild);
		aChild->SetChildIndex(aParent->GetChildCount() - 1);

		gameobjectIdsThatAreOpen.emplace(aParent->GetID());
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
				else if (ImGui::BeginMenu("UI"))
				{
					if (ImGui::MenuItem("Canvas"))
					{
						GameObject* obj = ComponentManager::CreateGameObject();
						obj->AddComponent<Transform2D>();
						obj->AddComponent<Canvas>();

						obj->SetName("Canvas");
					}
					else if (ImGui::MenuItem("Image"))
					{
						GameObject* obj = ComponentManager::CreateGameObject();
						obj->AddComponent<Transform2D>();
						obj->AddComponent<RectTransform>();
						obj->AddComponent<UIImage>();

						obj->SetName("Image");
					}
					else if (ImGui::MenuItem("Text"))
					{
						GameObject* obj = ComponentManager::CreateGameObject();
						obj->AddComponent<Transform2D>();
						obj->AddComponent<TextRenderer>();
						obj->AddComponent<TextRenderer>();

						obj->SetName("New Text");
					}
					ImGui::EndMenu();
				}

				ImGui::EndMenu();
			}

			ImGui::EndPopup();
		}

		if (ImGui::IsKeyPressed(ImGuiKey_Delete))
		{
			unsigned currentObject = HierarchyWindow::CurrentGameObjectID;
			if (currentObject > 0)
			{
				GameObject* gameobject = ComponentManager::myEntityIdToEntity.at(currentObject);
				RecursiveDeleteChildren(gameobject);

				gameobjectIdsThatAreOpen.erase(currentObject);
				HierarchyWindow::CurrentGameObjectID = 0;

			}
		}


		for (const auto& [id, data] : ComponentManager::myEntityIdToEntity)
		{
			GameObject* parent = data->GetParent();
			if (parent)
				continue;

			HierarchyButton(data, 0.f);
		}
	}

	void HierarchyWindow::RecursiveDeleteChildren(GameObject*& aGameObject)
	{
		auto& children = aGameObject->GetChildren();
		for (auto& child : children)
		{
			RecursiveDeleteChildren(child);
		}

		ComponentManager::Destroy(aGameObject->GetID());
	}
}
#endif