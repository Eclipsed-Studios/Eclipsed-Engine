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

#include "CoreEngine/GameObject.h"

#include "Utilities/WindowsSpecific/Clipboard.h"

namespace Eclipse::Editor
{
	void HierarchyWindow::HierarchyButton(GameObject* aGameObject, float totalIndent)
	{
		unsigned id = aGameObject->GetID();

		ImGui::Dummy(ImVec2(totalIndent, 0.f));
		ImGui::SameLine();
		if (ImGui::Button(std::string(aGameObject->GetName() + "##" + std::to_string(id)).c_str()))
		{
			CurrentGameObjectID = id;
			InspectorWindow::activeType = ActiveItemTypes_GameObject;
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

		std::vector<GameObject*> children = aGameObject->GetChildren();
		totalIndent += 32.f;
		for (auto& child : children)
		{
			HierarchyButton(child, totalIndent);
		}
	}

	void HierarchyWindow::AssignParentChildren(GameObject* targetGO, Eclipse::GameObject* aGameObject)
	{
		if (auto& parent = targetGO->GetParent())
		{
			if (targetGO->GetParent()->GetID() == aGameObject->GetID())
				return;

			auto& children = parent->GetChildren();
			size_t childIndex = targetGO->GetChildIndex();

			for (int i = childIndex; i < children.size() - 1; i++)
				children[i] = children[i + 1];

			children.pop_back();
		}

		targetGO->SetParent(aGameObject);

		aGameObject->AddChild(targetGO);
		targetGO->SetChildIndex(aGameObject->GetChildCount() - 1);
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
			GameObject* parent = data->GetParent();
			if (parent)
				continue;
			HierarchyButton(data, 0.f);
		}

		CopyPasteManager();
	}

	void HierarchyWindow::Copy()
	{
		if (CurrentGameObjectID <= 0)
			return;

		rapidjson::Document d;
		d.SetObject();

		rapidjson::Document::AllocatorType& jsonAllocator = d.GetAllocator();

		auto& reflectionList = Reflection::ReflectionManager::GetList();
		for (Component* pComp : ComponentManager::myComponents)
		{
			std::string compName = pComp->GetComponentName();

			if (compName == "Component")
				continue;

			rapidjson::Value value(rapidjson::kObjectType);

			value.AddMember("name", rapidjson::Value(compName.c_str(), jsonAllocator).Move(), jsonAllocator);

			for (auto& var : reflectionList.at(pComp))
			{
				std::string compName = var->GetComponent()->GetComponentName();
				Component* pComp = var->GetComponent();

				SceneLoader::WriteMember(value, var, jsonAllocator);
			}

			d.AddMember("Component", value, jsonAllocator);
		}

		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		d.Accept(writer);

		const char* bufferString = buffer.GetString();
		int stringLength = strlen(bufferString);

		ClipBoard::CopyToClipboard(bufferString, stringLength);
	}

	void HierarchyWindow::Paste()
	{
		char* dataInt = (char*)ClipBoard::GetClipboardData();

		int i = 0;

		// for (auto& vec : myCopiedComponentsFromObjects)
		// {
		// 	if (vec.size() == 0)
		// 		continue;

		// 	GameObject* newGO = ComponentManager::CreateGameObjectNoTransform();
		// 	for (auto* ogComponent : vec)
		// 	{
		// 		Component* component;

		// 		component = ComponentRegistry::GetAddComponent(ogComponent->GetComponentName())(*newGO, Component::nextComponentID++);

		// 		auto& reflectedList = Reflection::ReflectionManager::GetList();
		// 		if (reflectedList.find(component) == reflectedList.end())
		// 			continue;

		// 		auto& reflectedVars = reflectedList.at(component);
		// 		auto& reflectedVarsOGComponent = Reflection::ReflectionManager::GetList().at(ogComponent);

		// 		for (int i = 0; i < reflectedVars.size(); i++)
		// 		{
		// 			auto& newVariable = reflectedVars[i];
		// 			auto& ogVariable = reflectedVarsOGComponent[i];

		// 			newVariable->ResolveTypeInfo();
		// 			ogVariable->ResolveTypeInfo();

		// 			switch (ogVariable->GetType())
		// 			{
		// 			case Reflection::AbstractSerializedVariable::SerializedType_String:
		// 			{
		// 				std::string& stringRef = *reinterpret_cast<std::string*>(newVariable->GetData());
		// 				stringRef = *reinterpret_cast<std::string*>(ogVariable->GetData());
		// 			}
		// 			break;


		// 			case Reflection::AbstractSerializedVariable::SerializedType_List:
		// 				newVariable->Resize(ogVariable->GetCount());
		// 			default:
		// 				std::memcpy(newVariable->GetData(), ogVariable->GetData(), ogVariable->GetSizeInBytes());
		// 				break;
		// 			}

		// 		}
		// 	}

		// 	for (auto& component : ComponentManager::GetComponents(newGO->GetID()))
		// 		component->OnSceneLoaded();

		// 	CurrentGameObjectID = newGO->GetID();
		// }
	}

	void HierarchyWindow::CopyPasteManager()
	{
		if (ImGui::IsAnyItemActive())
			return;

		bool ctrlHeld = ImGui::IsKeyDown(ImGuiKey_LeftCtrl) || ImGui::IsKeyDown(ImGuiKey_RightCtrl);

		if (ctrlHeld && ImGui::IsKeyPressed(ImGuiKey_C))
			Copy();
		else if (ctrlHeld && ImGui::IsKeyPressed(ImGuiKey_V))
			Paste();
		else if (ctrlHeld && ImGui::IsKeyPressed(ImGuiKey_D))
		{
			Copy();
			Paste();
		}

		// Duplicate by helf Alt + Drag is in gameobject picker function
	}
}
#endif