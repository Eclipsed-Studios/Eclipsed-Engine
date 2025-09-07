#include "InspectorWindow.h"

#include "HierarchyWindow.h"

#include "ECS/ComponentManager.h"

#include "FontAwesomeRegular.h"
#include "IconsFontAwesome6.h"

namespace ENGINE_NAMESPACE::Editor
{
	InspectorWindow::InspectorWindow(const int& aId)
	{
		myWindowName = "Inspector";
		myID = aId == -1 ? Random::GetValue<int>() : aId;

		auto& io = ImGui::GetIO();
	}
	void InspectorWindow::Open()
	{
	}
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
			DrawInspector(comp);
		}
	}
	void InspectorWindow::Close()
	{
	}


	void InspectorWindow::DrawComponentHeader(const char* compName, bool& isDrawn, const float values, ImGuiStyleVar styleFlags)
	{
		ImGui::PushStyleVar(styleFlags, values);
		isDrawn = ImGui::CollapsingHeader(compName);
		ImGui::PopStyleVar();
	}
}