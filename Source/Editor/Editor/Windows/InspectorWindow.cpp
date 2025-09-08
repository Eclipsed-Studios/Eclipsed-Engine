#include "InspectorWindow.h"

#include "HierarchyWindow.h"

#include "ECS/ComponentManager.h"

#include "FontAwesomeRegular.h"
#include "IconsFontAwesome6.h"
#include "Editor/ImGui/ImGui_Impl.h"

namespace ENGINE_NAMESPACE::Editor
{
	void InspectorWindow::Update()
	{
		const unsigned& id = HierarchyWindow::CurrentGameObjectID;
		if (id == 0) return;

		auto& compList = ComponentManager::myEntityIDToVectorOfComponentIDs[id];
		auto& compData = ComponentManager::myEntityIdToEntityData[id];

		// TODO: This bad, it copies every frame. But who cares, am i right?
		strncpy(nameBuffer, compData.name.c_str(), NAME_BUFFER_LENGTH);

		ImGui::Text("Name");
		ImGui::SameLine();

		if (ImGui::InputText((std::string("##") + std::to_string(id)).c_str(), nameBuffer, NAME_BUFFER_LENGTH))
		{
			compData.name = nameBuffer;
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
		}
	}
}