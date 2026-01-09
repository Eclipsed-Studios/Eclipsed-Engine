#include "InspectorWindow.h"
#include "HierarchyWindow.h"

#include "EntityEngine/ComponentManager.h"

#include "EclipsedEngine/Editor/ImGui/ImGui_Impl.h"

#include "EclipsedEngine/Reflection/Registry/ComponentRegistry.h"

#include "EclipsedEngine/Components/Transform2D.h"
#include "EclipsedEngine/Components/Rendering/SpriteRenderer2D.h"
#include "EclipsedEngine/Components/Rendering/SpriteSheetAnimator.h"
#include "EclipsedEngine/Components/AudioSource.h"

#include "SpriteEditor.h"

#include "ImGui/imgui.h"

#include "AssetEngine/Models/AssetDatas/Binary/MaterialBinaryData.h"

#include "AssetEngine/AssetRegistry.h"

#include "EclipsedEngine/Editor/Windows/WindowTypes/AssetWindow/AssetWindow.h"
#include "EclipsedEngine/Editor/Common/DragAndDrop.h"

#include <sstream>
#include <fstream>

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
		if (!lockInspector)
		{
			CurrentGameObjectID = HierarchyWindow::CurrentGameObjectID;
		}

		const unsigned& id = CurrentGameObjectID;
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

		ImGui::SetNextItemWidth(120);
		if (ImGui::InputText((std::string("##") + std::to_string(id)).c_str(), nameBuffer, NAME_BUFFER_LENGTH))
		{
			gameObject->SetName(nameBuffer);
		}

		unsigned localID = gameObject->GetID();

		std::stringstream idStream;
		idStream << "ID: " << localID;

		ImGui::Text(idStream.str().c_str());

		ImGui::SetCursorPosX(ImGui::GetWindowSize().x - 48);
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 6);
		ImGui::Text(ICON_FA_LOCK);
		ImGui::SameLine();
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 6);
		ImGui::Checkbox("##lockinspector", &lockInspector);

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

			unsigned localComponentID = comp->myInstanceComponentID;
			std::stringstream componentIDStream;
			componentIDStream << "ID: " << localComponentID;
			ImGui::Text(componentIDStream.str().c_str());

			ImGui::Indent(20.f);
			Reflection::ReflectionManager::DrawInspector(comp, comp->GetComponentName());
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

	void InspectorWindow::DrawComponentInspector(Component* comp)
	{
		int i = 0;
		i++;
		i--;
		i = 924;
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

		{ // Texture dnd
			bool textClicked = false, arrowClicked = false;
			std::string text = "No Texture";
			if (data.textureID != 0)
			{
				auto& entry = registry.GetRegisteredAsset(data.textureID);
				text = entry.path.filename().generic_string();
			}

			if (DragAndDrop::BeginTarget(text.c_str(), Utilities::FileInfo::FileType_Texture, &textClicked, &arrowClicked))
			{
				data.textureID = registry.GetIdFromPath(DragAndDrop::payloadBuffer);
				changed = true;
			}

			if (arrowClicked)
			{
				ImGui::OpenPopup("##dropdown_popup");
			}

			if (ImGui::BeginPopup("##dropdown_popup"))
			{
				// Optional: title or search bar
				ImGui::TextUnformatted("Select Texture");
				ImGui::Separator();

				if (ImGui::Selectable("None"))
				{
					data.textureID = 0;
					changed = true;
				}

				for (const size_t& assetId : registry.GetAllAssetsOfType(Assets::AssetType::Texture))
				{
					const Assets::AssetRegistryEntry& entry = registry.GetRegisteredAsset(assetId);
					std::string name = entry.path.filename().string();

					if (ImGui::Selectable(name.c_str()))
					{
						data.textureID = assetId;
						ImGui::CloseCurrentPopup();
						changed = true;
					}
				}

				ImGui::EndPopup();
			}
		}

		ImGui::Spacing();

		{ // Pixel shader dnd
			std::string text = "No Pixel Shader";
			if (data.pixelShaderID != 0)
			{
				auto& entry = registry.GetRegisteredAsset(data.pixelShaderID);
				text = entry.path.filename().generic_string();
			}

			if (DragAndDrop::BeginTarget(text.c_str(), Utilities::FileInfo::FileType_PixelShader))
			{
				data.pixelShaderID = registry.GetIdFromPath(DragAndDrop::payloadBuffer);
				changed = true;
			}
		}

		ImGui::Spacing();

		{ // Vertex shader dnd
			std::string text = "No Vertex Shader";
			if (data.vertexShaderID != 0)
			{
				auto& entry = registry.GetRegisteredAsset(data.vertexShaderID);
				text = entry.path.filename().generic_string();
			}

			if (DragAndDrop::BeginTarget(text.c_str(), Utilities::FileInfo::FileType_PixelShader))
			{
				data.vertexShaderID = registry.GetIdFromPath(DragAndDrop::payloadBuffer);
				changed = true;
			}
		}

		if (changed)
		{
			auto rel = std::filesystem::relative(AssetWindow::ActivePath, PathManager::GetAssetDir());

			registry.RegisterChange(rel);

			std::ofstream out(AssetWindow::ActivePath, std::ios::binary);
			out.write(reinterpret_cast<const char*>(&data), sizeof(Assets::MaterialBinaryData));
			out.close();
		}
	}
}