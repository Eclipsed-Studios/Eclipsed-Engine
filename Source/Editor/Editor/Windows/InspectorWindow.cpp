#include "InspectorWindow.h"
#include "HierarchyWindow.h"

#include "ECS/ComponentManager.h"

#include "FontAwesomeRegular.h"
#include "IconsFontAwesome6.h"
#include "Editor/ImGui/ImGui_Impl.h"

#include "Reflection/Registry/ComponentRegistry.h"

#include "Components/Transform2D.h"
#include "Components/Rendering/SpriteRenderer2D.h"
#include "Components/Rendering/SpriteSheetAnimator.h"
#include "Components/AudioSource.h"

#include "ImGui/imgui.h"

namespace Eclipse::Editor
{
	void InspectorWindow::Update()
	{
		const unsigned& id = HierarchyWindow::CurrentGameObjectID;
		if (id == 0) return;

		auto& compList = ComponentManager::myEntityIDToVectorOfComponentIDs[id];
		auto& gameObject = ComponentManager::myEntityIdToEntity[id];

		// TODO: This bad, it copies every frame. But who cares, am i right?
		strncpy(nameBuffer, gameObject->GetName().c_str(), NAME_BUFFER_LENGTH);

		ImGui::Text("Name");
		ImGui::SameLine();

		if (ImGui::InputText((std::string("##") + std::to_string(id)).c_str(), nameBuffer, NAME_BUFFER_LENGTH))
		{
			gameObject->SetName(nameBuffer);
		}

		ImGui::Dummy({ 0, 10 });
		ImGui::Separator();
		ImGui::Dummy({ 0, 5 });


		for (auto& [type, id] : compList)
		{
			Component* comp = ComponentManager::myComponents[id];
			ImGui_Impl::DrawComponentHeader(comp->GetComponentName(), comp->myInspectorWasDrawn);
			if (!comp->myInspectorWasDrawn) continue;

			comp->DrawInspector();

			ImGui::Dummy({0, 30});
			ImGui::Separator();
		}

		
		if (ImGui::BeginCombo("##ADD_COMPONENTS", "Add Component"))
		{
			for (auto& [name, addFunc] : ComponentRegistry::GetAddComponentMap())
			{
				if (ImGui::Button(name.c_str(), ImVec2(-FLT_MIN, 0)))
				{
					auto func = ComponentRegistry::GetAddComponent(name);
					func(id, Component::nextComponentID);
					ImGui::CloseCurrentPopup();
				}
			}

			ImGui::EndCombo();
		}
	}
}