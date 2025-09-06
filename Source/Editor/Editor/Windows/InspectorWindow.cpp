#include "InspectorWindow.h"

#include "HierarchyWindow.h"

#include "ImGui/imgui.h"
#include "ECS/ComponentManager.h"

namespace ENGINE_NAMESPACE::Editor
{
	InspectorWindow::InspectorWindow(const int& aId)
	{
		myWindowName = "Inspector";
		myID = aId == -1 ? rand() : aId;
	}
	void InspectorWindow::Open()
	{
	}
	void InspectorWindow::Update()
	{
		const unsigned& id = HierarchyWindow::CurrentGameObjectID;

		auto& compList = ComponentManager::myEntityIDToVectorOfComponentIDs[id];

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