#ifdef _EDITOR
#include "InspectorWindow.h"
#include "HierarchyWindow.h"

#include "ECS/ComponentManager.h"

#include "Editor/ImGui/ImGui_Impl.h"

#include "Reflection/Registry/ComponentRegistry.h"

#include "Components/Transform2D.h"
#include "Components/Rendering/SpriteRenderer2D.h"
#include "Components/Rendering/SpriteSheetAnimator.h"
#include "Components/AudioSource.h"

#include "SpriteEditor.h"

#include "ImGui/imgui.h"

namespace Eclipse::Editor
{
	void InspectorWindow::Update()
	{
		switch (activeType)
		{
		case Eclipse::Editor::ActiveItemTypes_GameObject: DrawGameObjectInspector();
			break;
		case Eclipse::Editor::ActiveItemTypes_Asset: DrawAssetInspector();
			break;
		}
	}

	void InspectorWindow::DrawGameObjectInspector()
	{
		const unsigned& id = HierarchyWindow::CurrentGameObjectID;
		if (id == 0 || !ComponentManager::HasGameObject(id))
			return;

		// Transform2D* idTransform = ComponentManager::GetComponent<Transform2D>(id);
		// DebugDrawer::DrawSquare(idTransform->GetPosition(), idTransform->GetScale() * 0.5f, {1, 0.6f, 0.f, 1.f});

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

		ImGui::BeginDisabled();
		ImGui::Text("ID");
		ImGui::SameLine();
		unsigned awawada = gameObject->GetID();

		ImGui::InputInt("##ID FIELDS", (int*)&awawada);
		ImGui::EndDisabled();

		ImGui::Dummy({ 0, 10 });
		ImGui::Separator();
		ImGui::Dummy({ 0, 5 });


		std::vector<Component*> comps;
		for (auto& [type, id] : compList)
		{
			Component* comp = ComponentManager::myComponents[id];
			comps.push_back(comp);
		}

		std::sort(comps.begin(), comps.end(),
			[](Component* a, Component* b) {
				return a->GetUpdatePriority() > b->GetUpdatePriority();
			});

		for (Component* comp : comps)
		{
			ImGui_Impl::DrawComponentHeader(comp->GetComponentName(), comp->myInspectorWasDrawn);
			if (!comp->myInspectorWasDrawn) continue;

			ImGui::Indent(20.f);
			comp->UpdateInspector();
			ImGui::Unindent(20.f);

			ImGui::Dummy({ 0, 30 });
			ImGui::Separator();
		}


		if (ImGui::BeginCombo("##ADD_COMPONENTS", "Add Component"))
		{
			for (auto& [name, addFunc] : ComponentRegistry::GetInspectorAddComponentMap())
			{
				if (ImGui::Button(name.c_str(), ImVec2(-FLT_MIN, 0)))
				{
					addFunc(id);
					ImGui::CloseCurrentPopup();
				}
			}

			ImGui::EndCombo();
		}
	}

	void InspectorWindow::DrawAssetInspector()
	{
		ImGui::Text(AssetWindow::Active_FilePath.filename().string().c_str());

		Utilities::FileInfo info = Utilities::FileInfo::GetFileInfo(AssetWindow::Active_FilePath);
		if (info.type == Utilities::FileInfo::FileType_Texture)
			DrawTextureAssetInspector();
		
	}

	void InspectorWindow::DrawTextureAssetInspector()
	{
		if (ImGui::Button("Open Editor"))
		{
			SpriteEditor::SetTexture(AssetWindow::Active_FilePath.string().c_str());
		}
	}
}
#endif