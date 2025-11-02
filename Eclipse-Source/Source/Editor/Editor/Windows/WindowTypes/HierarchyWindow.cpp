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

#include "CoreEngine\Scenes\SceneLoader.h"

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

	void HierarchyWindow::AssignParentChildren(GameObject* aChild, Eclipse::GameObject* aParent)
	{
		if (auto& parent = aChild->GetParent())
		{
			if (aChild->GetParent()->GetID() == aParent->GetID())
				return;

			auto& children = parent->GetChildren();
			size_t childIndex = aChild->GetChildIndex();

			for (int i = childIndex; i < children.size() - 1; i++)
			{
				children[i] = children[i + 1];
				children[i]->SetChildIndex(i);
			}

			children.pop_back();
		}

		Math::Vector2f childPos = aChild->transform->GetPosition();

		Math::Matrix3x3f newParentTransformMatrix = aParent->transform->GetTransformMatrix();

		Math::Vector3f positionVec3(childPos.x, childPos.y, 1);
		Math::Vector3f positionVec3ParentSpace = positionVec3 * newParentTransformMatrix;

		childPos = { positionVec3ParentSpace.x, positionVec3ParentSpace.y };

		aChild->SetParent(aParent);

		aParent->AddChild(aChild);
		aChild->SetChildIndex(aParent->GetChildCount() - 1);

		aChild->transform->SetPosition(childPos);
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

	void HierarchyWindow::CopyGameObject(unsigned activeGO, rapidjson::Value& gameobjectJson, rapidjson::Document::AllocatorType& anAllocator)
	{
		rapidjson::Value componentArray(rapidjson::kArrayType);
		componentArray.SetArray();

		auto& reflectionList = Reflection::ReflectionManager::GetList();
		auto components = ComponentManager::GetComponents(activeGO);
		for (Component* pComp : components)
		{
			std::string compName = pComp->GetComponentName();

			if (compName == "Component")
				continue;

			rapidjson::Value component(rapidjson::kObjectType);

			rapidjson::Value componentVars(rapidjson::kObjectType);
			for (auto& var : reflectionList.at(pComp))
			{
				SceneLoader::WriteMember(componentVars, var, anAllocator);
			}
			component.AddMember(rapidjson::Value(compName.c_str(), anAllocator).Move(), componentVars, anAllocator);
			componentArray.PushBack(component, anAllocator);
		}
		gameobjectJson.AddMember("Name", rapidjson::Value(ComponentManager::myEntityIdToEntity.at(CurrentGameObjectID)->GetName().c_str(), anAllocator), anAllocator);
		gameobjectJson.AddMember("Components", componentArray, anAllocator);

		rapidjson::Value childArray(rapidjson::kArrayType);
		childArray.SetArray();

		auto& activeGameObjectObject = ComponentManager::myEntityIdToEntity.at(activeGO);

		if (activeGameObjectObject->GetChildCount())
		{
			for (auto& child : ComponentManager::myEntityIdToEntity.at(activeGO)->GetChildren())
			{
				rapidjson::Value childObject(rapidjson::kObjectType);
				childObject.SetObject();

				CopyGameObject(child->GetID(), childObject, anAllocator);

				childArray.PushBack(childObject, anAllocator);
			}

			gameobjectJson.AddMember("Children", childArray, anAllocator);
		}
	}

	void HierarchyWindow::Copy()
	{
		if (CurrentGameObjectID <= 0)
			return;

		rapidjson::Document d;
		d.SetObject();

		rapidjson::Document::AllocatorType& jsonAllocator = d.GetAllocator();

		rapidjson::Value gameObjectArrayJson(rapidjson::kArrayType);
		gameObjectArrayJson.SetArray();

		rapidjson::Value gameobjectJson(rapidjson::kObjectType);
		gameobjectJson.SetObject();

		CopyGameObject(CurrentGameObjectID, gameobjectJson, jsonAllocator);

		gameObjectArrayJson.PushBack(gameobjectJson, jsonAllocator);
		d.AddMember("Gameobjects", gameObjectArrayJson, jsonAllocator);

		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		d.Accept(writer);

		const char* bufferString = buffer.GetString();
		int stringLength = strlen(bufferString);

		ClipBoard::CopyToClipboard(bufferString, stringLength);
	}

	void HierarchyWindow::PasteGameObject(GameObject*& aGameObject, rapidjson::Value& gameobject, rapidjson::Document::AllocatorType& anAllocator)
	{
		aGameObject = ComponentManager::CreateGameObjectNoTransform();
		aGameObject->SetName(gameobject["Name"].GetString());

		for (auto& components : gameobject["Components"].GetArray())
		{
			for (auto coIt = components.MemberBegin(); coIt != components.MemberEnd(); coIt++)
			{
				Component* component;
				component = ComponentRegistry::GetAddComponent(coIt->name.GetString())(*aGameObject, Component::nextComponentID++);

				auto& reflectedList = Reflection::ReflectionManager::GetList();
				if (reflectedList.find(component) == reflectedList.end())
					continue;

				auto& reflectedVars = reflectedList.at(component);

				int refIndex = 0;
				for (auto varIt = coIt->value.MemberBegin(); varIt != coIt->value.MemberEnd(); varIt++)
				{
					auto& reflectedVariable = reflectedVars.at(refIndex++);
					reflectedVariable->ResolveTypeInfo();

					if (reflectedVariable->GetType() == Reflection::AbstractSerializedVariable::SerializedType_String)
					{
						std::string strVal = varIt->value.GetString();

						std::string* str = (std::string*)reflectedVariable->GetData();
						str->resize(strVal.size());

						memcpy(str->data(), strVal.data(), strVal.size());
					}
					else if (reflectedVariable->GetType() == Reflection::AbstractSerializedVariable::SerializedType_List)
					{
						const unsigned count = varIt->value["size"].GetUint();
						reflectedVariable->Resize(count);

						const std::string strVal = varIt->value["data"].GetString();

						std::vector<unsigned char> decoded = Base64::Decode(strVal);
						memcpy(reflectedVariable->GetData(), decoded.data(), decoded.size());
					}
					else
					{
						std::string strVal = varIt->value.GetString();
						std::vector<unsigned char> decoded = Base64::Decode(strVal);
						memcpy(reflectedVariable->GetData(), decoded.data(), decoded.size());
					}
				}
			}
		}

		if (gameobject.HasMember("Children"))
		{
			auto childArray = gameobject["Children"].GetArray();
			for (auto& child : childArray)
			{
				GameObject* newGameObject;
				PasteGameObject(newGameObject, child, anAllocator);

				aGameObject->AddChild(newGameObject);
				newGameObject->SetParent(aGameObject);
			}
		}
	}

	void StartChildren(std::vector<GameObject*>& aChildComponents)
	{
		for (auto& child : aChildComponents)
		{
			if (child->GetChildCount() > 0)
				StartChildren(child->GetChildren());

			for (auto& component : ComponentManager::GetComponents(child->GetID()))
				component->OnSceneLoaded();

			for (auto& component : ComponentManager::GetComponents(child->GetID()))
				component->OnComponentAdded();
		}
	}

	void HierarchyWindow::Paste()
	{
		char* data = (char*)ClipBoard::GetClipboardData();

		rapidjson::Document d;
		d.SetObject();
		rapidjson::Document::AllocatorType& jsonAllocator = d.GetAllocator();

		d.Parse(data);

		for (auto& gameobject : d["Gameobjects"].GetArray())
		{
			GameObject* newGameobject;
			PasteGameObject(newGameobject, gameobject, jsonAllocator);

			if (newGameobject->GetChildCount() > 0)
				StartChildren(newGameobject->GetChildren());

			for (auto& component : ComponentManager::GetComponents(newGameobject->GetID()))
				component->OnSceneLoaded();

			for (auto& component : ComponentManager::GetComponents(newGameobject->GetID()))
				component->OnComponentAdded();

			CurrentGameObjectID = newGameobject->GetID();
		}
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