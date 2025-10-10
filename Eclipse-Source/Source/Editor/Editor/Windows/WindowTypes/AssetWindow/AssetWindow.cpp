#ifdef _EDITOR

#include "AssetWindow.h"
#include "Editor/Common/TextureIconManager.h"

#include "Scenes/SceneManager.h"

namespace Eclipse::Editor
{
	void AssetWindow::Open()
	{
		dirTree = Utilities::DirectoryTree(ASSET_PATH);
		Active_View_Node = dirTree.GetRoot();
	}

	void AssetWindow::Update()
	{
		DrawAssetHierachy();
		ImGui::SameLine();
		DrawAssetView();

		ctxMenu.Draw();
	}

	bool AssetWindow::CheckFileDoubleClicked()
	{
		if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
		{
			return true;
		}

		return false;
	}

	bool AssetWindow::CheckFileClicked()
	{
		if (ImGui::IsItemHovered() && ImGui::IsMouseDown(ImGuiMouseButton_Left) || ImGui::IsMouseDown(ImGuiMouseButton_Right))
		{
			return true;
		}

		return false;
	}


#pragma region -- ASSET TREE VIEW

	void AssetWindow::DrawAssetHierachy()
	{
		ImGui::BeginChild("FolderStructure", ImVec2(folderStructureWidth, ImGui::GetContentRegionAvail().y), true);

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));

		static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_DrawLinesFull | ImGuiTreeNodeFlags_DrawLinesToNodes | ImGuiTreeNodeFlags_DefaultOpen;
		if (ImGui::TreeNodeEx(ICON_FA_FOLDER " Assets", base_flags))
		{
			Utilities::FileNode* startNode = dirTree.GetNode(ASSET_PATH);

			DrawAssetHierachyEntry(startNode);
			ImGui::TreePop();
		}

		ImGui::PopStyleColor();

		ImGui::EndChild();
	}

	void AssetWindow::DrawAssetHierachyEntry(Utilities::FileNode* node)
	{
		namespace fs = std::filesystem;

		static ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_DrawLinesFull | ImGuiTreeNodeFlags_DrawLinesToNodes;

		for (std::unique_ptr<Utilities::FileNode>& child : node->children)
		{
			std::string name = child->info.filePath.filename().string();
			std::string icon = child->info.GetIcon();

			if (child->isDirectory && ImGui::TreeNodeEx((ICON_FA_FOLDER " " + name).c_str(), node_flags))
			{
				DrawAssetHierachyEntry(child.get());
				ImGui::TreePop();
			}
			else if (!child->isDirectory && ImGui::Button((icon + " " + name).c_str()))
			{
				Active_Hierarchy_Node = dirTree.GetNode(child->info.filePath);
			}
		}
	}

#pragma endregion






#pragma region -- ASSET VIEW
	void AssetWindow::DrawAssetViewBreadcrumb()
	{
		namespace fs = std::filesystem;

		std::string pathCombiner = ASSET_PATH;
		fs::path p = std::string("Assets/") + Active_View_Node->info.relativeFilePath.string();
		for (auto& path : p)
		{
			if (path.empty()) return;

			if (path.string() != "Assets")
			{
				ImGui::SameLine();

				ImVec2 pos = ImGui::GetCursorPos();
				ImGui::SetCursorPos(ImVec2(pos.x, pos.y - 2));
				ImGui::PushFont(EditorContext::fontMedium);
				ImGui::Text(">");
				ImGui::PopFont();

				pathCombiner += path.string();
				pathCombiner.push_back('/');
				ImGui::SameLine();
			}

			if (ImGui::Button(path.string().c_str()))
			{
				fs::path wantedPath(pathCombiner);
				Active_View_Node = dirTree.GetNode(wantedPath);
			}
		}
	}

	void AssetWindow::DrawAssetView()
	{
		namespace fs = std::filesystem;

		ImGui::BeginChild("AssetView");
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0, 0, 0));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0));

		DrawAssetViewBreadcrumb();

		ImGui::Separator();

		ImGui::Indent(10.f);

		for (std::unique_ptr<Utilities::FileNode>& node : Active_View_Node->children)
		{
			CheckAssetViewEntryClicked(node.get());
			entryIndex++;
		}

		ImGui::Unindent(10.f);

		ImGui::PopStyleColor(3);
		ImGui::EndChild();

		if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
		{
			ActivePath = "";
			ctxMenu.SetActivePath(ActivePath);
			ActiveEntryIndex = -1;
		}

		entryIndex = 0;
	}

	void AssetWindow::DrawAssetViewEntry(const Utilities::FileNode* node)
	{
		float customWidth = ImGui::GetWindowWidth() + scrollBarWidth;

		const float width = customWidth + ImGui::GetWindowPos().x - scrollBarWidth * 2;
		const float buttonSize = 100.0f * myButtonSizeMultiplier;
		const float padding = ImGui::GetStyle().ItemSpacing.x;


		ImVec2 pos = ImGui::GetCursorPos();

		const char* icon = node->info.GetIcon();

		ImGui::PushID((std::string("##") + node->info.filePath.string()).c_str());

		ImVec2 buttonSizeVec(buttonSize, buttonSize);

		ImColor col(1.f, 1.f, 1.f, 1.f);
		if (!ActivePath.empty() && entryIndex == ActiveEntryIndex) col = ImColor(1.00f, 0.75f, 0.30f, 1.00f);

		ImGui::PushFont(Editor::EditorContext::fontExtraLarge);
		ImGui::PushStyleColor(ImGuiCol_Text, col.Value);

		if (node->info.type == Utilities::FileInfo::FileType_Texture)
		{
			const IconData& data = IconManager::GetIcon(node->info);

			ImGui::InvisibleButton("##icon", buttonSizeVec);

			ImVec2 p_min = ImGui::GetItemRectMin();
			ImVec2 p_max = ImGui::GetItemRectMax();

			float availW = p_max.x - p_min.x;
			float availH = p_max.y - p_min.y;

			float texWidth = data.width;
			float texHeight = data.height;

			float scale = 0.6f;
			float maxDim = std::min(availW, availH) * scale;

			float ratio = texWidth / texHeight;
			float drawWidth, drawHeight;

			if (ratio > 1.0f)
			{
				drawWidth = maxDim;
				drawHeight = maxDim / ratio;
			}
			else
			{
				drawHeight = maxDim;
				drawWidth = maxDim * ratio;
			}

			ImVec2 center((p_min.x + p_max.x) * 0.5f, (p_min.y + p_max.y) * 0.5f);
			ImVec2 imageMin(center.x - drawWidth * 0.5f, center.y - drawHeight * 0.5f);
			ImVec2 imageMax(center.x + drawWidth * 0.5f, center.y + drawHeight * 0.5f);

			ImGui::GetWindowDrawList()->AddImage(
				(ImTextureID)data.textureID,
				imageMin, imageMax,
				ImVec2(0, 0), ImVec2(1, 1),
				col
			);
		}
		else
		{
			ImGui::Button(icon, buttonSizeVec);
		}

		ImGui::PopStyleColor();
		ImGui::PopFont();

		DragAndDrop::BeginSource(node->info.relativeFilePath.string().c_str(), node->info.relativeFilePath.string().size(), node->info);

		std::string label = node->info.filePath.filename().string();
		const float maxSize = buttonSize - 86.f;
		if (label.size() > maxSize)
		{
			label.erase(maxSize, label.size());
			label += "...";
		}

		ImVec2 min = ImGui::GetItemRectMin();
		ImVec2 max = ImGui::GetItemRectMax();
		if (entryIndex == ActiveEntryIndex)
		{
			ImGui::GetWindowDrawList()->AddRect(min, max, ImColor(1.00f, 0.75f, 0.30f, 1.00f), 6.f);
			ImGui::GetWindowDrawList()->AddRectFilled(min, max, ImColor(1.00f, 0.75f, 0.30f, 0.2f), 6.f);
		}

		if (ImGui::IsItemHovered())
		{
			ImGui::GetWindowDrawList()->AddRect(min, max, ImColor(0.95f, 0.60f, 0.20f, 0.85f), 6.f);
			ImGui::GetWindowDrawList()->AddRectFilled(min, max, ImColor(0.95f, 0.60f, 0.20f, 0.2f), 6.f);
		}

		ImVec2 center = ImVec2((min.x + max.x) * 0.5f, (min.y + max.y) * 0.5f);

		ImGui::PushFont(Editor::EditorContext::fontTiny);
		ImVec2 textSize = ImGui::CalcTextSize(label.c_str());
		const char* end = label.c_str() + 10;
		ImGui::GetWindowDrawList()->AddText(
			Editor::EditorContext::fontTiny,
			0.0f,
			ImVec2(center.x - textSize.x * 0.5f, max.y - textSize.y - 6),
			col,
			label.c_str()
		);

		ImGui::PopFont();



		ImGui::PopID();

		if (ImGui::IsItemHovered() && (ImGui::IsMouseReleased(ImGuiMouseButton_Left) || ImGui::IsMouseClicked(ImGuiMouseButton_Right)))
		{
			ActivePath = node->info.filePath;
			InspectorWindow::activeType = ActiveItemTypes_Asset;
			ActiveEntryIndex = entryIndex;

			ctxMenu.SetActivePath(ActivePath);
		}

		float currentWidth = ImGui::GetItemRectMax().x;

		if (currentWidth + buttonSize + padding < width)
		{
			ImGui::SameLine();
		}
	}

	void AssetWindow::CheckAssetViewEntryClicked(const Utilities::FileNode* node)
	{
		DrawAssetViewEntry(node);

		if (!CheckFileDoubleClicked()) return;

		if (node->isDirectory)
		{
			ActivePath = node->info.filePath;
			Active_View_Node = dirTree.GetNode(node->info.filePath);
		}
		else
		{
			ActivePath = node->info.filePath;
			OpenFile(node->info);
		}
	}
#pragma endregion

	void AssetWindow::OpenFile(const Utilities::FileInfo& fifo)
	{
		switch (fifo.type)
		{
		case Utilities::FileInfo::FileType_Scene:
			SceneManager::LoadScene(fifo.filePath.string());
			break;

		default:
			system(fifo.filePath.string().c_str());
			break;
		}
	}
}
#endif