#ifdef _EDITOR

#include "NewAssetWindow.h"
#include "Editor/TextureIconManager.h"

namespace Eclipse::Editor
{
	void NewAssetWindow::Open()
	{
		dirTree = Utilities::DirectoryTree(ASSET_PATH);
		ActiveNode = dirTree.GetRoot();
	}

	void NewAssetWindow::Update()
	{
		DrawAssetView();

	}

	bool NewAssetWindow::CheckFileClicked()
	{
		if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
		{
			return true;
		}

		return false;
	}


#pragma region -- ASSET TREE VIEW



#pragma endregion






#pragma region -- ASSET VIEW
	void NewAssetWindow::D()
	{
		namespace fs = std::filesystem;

		std::string pathCombiner = ASSET_PATH;
		fs::path p = std::string("Assets/") + ActiveNode->info.relativeFilePath.string();
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

				fs::path current = ActiveNode->info.filePath;
				fs::path wanted = wantedPath;

				while (current != wanted)
				{
					current = current.parent_path();
				}

				ActiveNode = dirTree.GetNode(current);
			}
		}
	}

	void NewAssetWindow::DrawAssetView()
	{
		namespace fs = std::filesystem;

		ImGui::BeginChild("AssetView");
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0, 0, 0));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0));

		D();

		ImGui::Separator();

		for (std::unique_ptr<Utilities::FileNode>& node : ActiveNode->children)
		{
			CheckAssetViewEntryClicked(node.get());
		}

		ImGui::PopStyleColor(3);
		ImGui::EndChild();
	}

	void NewAssetWindow::DrawAssetViewEntry(const Utilities::FileNode* node)
	{
		float customWidth = ImGui::GetWindowWidth() - folderStructureWidth + scrollBarWidth;

		const float width = customWidth + ImGui::GetWindowPos().x - scrollBarWidth * 2;
		const float buttonSize = 100.0f * myButtonSizeMultiplier;
		const float padding = ImGui::GetStyle().ItemSpacing.x;


		ImVec2 pos = ImGui::GetCursorPos();

		const char* icon = node->info.GetIcon();

		ImGui::PushID((std::string("##") + node->info.filePath.string()).c_str());

		ImVec2 buttonSizeVec(buttonSize, buttonSize);

		ImColor col(200, 200, 200, 255);
		if (!ActivePath.empty() && std::filesystem::equivalent(ActivePath, node->info.filePath))
		{
			col = ImColor(150, 150, 255, 255);
		}


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
		ImVec2 center = ImVec2((min.x + max.x) * 0.5f, (min.y + max.y) * 0.5f);

		ImGui::PushFont(Editor::EditorContext::fontTiny);
		ImVec2 textSize = ImGui::CalcTextSize(label.c_str());
		const char* end = label.c_str() + 10;
		ImGui::GetWindowDrawList()->AddText(
			Editor::EditorContext::fontTiny,
			0.0f,
			ImVec2(center.x - textSize.x * 0.5f, max.y - textSize.y - 6),
			IM_COL32(255, 255, 255, 255),
			label.c_str()
		);

		ImGui::PopFont();



		ImGui::PopID();

		if (ImGui::IsItemHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Left))
		{
			ActivePath = node->info.filePath;
			InspectorWindow::activeType = ActiveItemTypes_Asset;
		}
		else if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
		{
			ActivePath = node->info.filePath;
			ImGui::OpenPopup("AssetContextMenu");
		}

		float currentWidth = ImGui::GetItemRectMax().x;

		if (currentWidth + buttonSize + padding < width)
		{
			ImGui::SameLine();
		}
	}

	void NewAssetWindow::CheckAssetViewEntryClicked(const Utilities::FileNode* node)
	{
		DrawAssetViewEntry(node);

		bool isClicked = CheckFileClicked();
		if (isClicked && node->isDirectory)
		{
			ActivePath = node->info.filePath;
			ActiveNode = dirTree.GetNode(node->info.filePath);
		}

	}
#pragma endregion
}
#endif