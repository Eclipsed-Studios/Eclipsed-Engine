#ifdef ECLIPSED_EDITOR
#include "InspectorWindow.h"
#include "HierarchyWindow.h"

#include "CoreEngine/ECS/ComponentManager.h"

#include "Editor/ImGui/ImGui_Impl.h"

#include "Utilities/Reflection/Registry/ComponentRegistry.h"

#include "CoreEngine/Components/Transform2D.h"
#include "CoreEngine/Components/Rendering/SpriteRenderer2D.h"
#include "CoreEngine/Components/Rendering/SpriteSheetAnimator.h"
#include "CoreEngine/Components/AudioSource.h"

#include "SpriteEditor.h"

#include "ImGui/imgui.h"

#include "AssetEngine/Models/AssetDatas/Binary/MaterialBinaryData.h"

#include "AssetEngine/AssetRegistry.h"

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
		ImGui::Text(AssetWindow::ActivePath.filename().string().c_str());

		Utilities::FileInfo info = Utilities::FileInfo::GetFileInfo(AssetWindow::ActivePath);
		if (info.type == Utilities::FileInfo::FileType_Texture)
			DrawTextureAssetInspector();
		else if (info.type == Utilities::FileInfo::FileType_Material)
			DrawMaterialAssetInspector();

	}

	void InspectorWindow::DrawTextureAssetInspector()
	{
		if (ImGui::Button("Open Editor"))
		{
			std::filesystem::path relPath = std::filesystem::relative(AssetWindow::ActivePath, PathManager::GetAssetDir());

			SpriteEditor::SetTexture(relPath.string().c_str());
		}
	}

	void InspectorWindow::DrawMaterialAssetInspector()
	{
		static Assets::MaterialBinaryData data;

		std::ifstream in(AssetWindow::ActivePath, std::ios::binary);
		in.read(reinterpret_cast<char*>(&data), sizeof(Assets::MaterialBinaryData));
		in.close();

		 bool changed = ImGui::ColorEdit4("Material Color", data.color.data,
			ImGuiColorEditFlags_AlphaBar |
			ImGuiColorEditFlags_AlphaPreview |
			ImGuiColorEditFlags_PickerHueWheel |
			ImGuiColorEditFlags_DisplayRGB |
			ImGuiColorEditFlags_NoInputs);

		 Assets::AssetRegistry& registry = Assets::AssetRegistry::GetInstance();

		 std::string title = "No Texture";
		 if (data.textureID != 0)
		 {
			 auto& entry = registry.GetRegisteredAsset(data.textureID);
			 title = entry.path.filename().generic_string();	
		 }

		 if (DragAndDrop::BeginTarget(title.c_str(), Utilities::FileInfo::FileType_Texture))
		 {
			 data.textureID = registry.GetIdFromPath(DragAndDrop::payloadBuffer);
			 changed = true;
		 }

		if (changed)
		{
			std::ofstream out(AssetWindow::ActivePath, std::ios::binary);
			out.write(reinterpret_cast<const char*>(&data), sizeof(Assets::MaterialBinaryData));
			out.close();
		}
	}
}
#endif