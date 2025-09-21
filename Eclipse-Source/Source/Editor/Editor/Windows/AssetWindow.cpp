#ifdef _EDITOR
#include "AssetWindow.h"

#include "ImGui/imgui.h"
#include "ECS/ComponentManager.h"

#include "Input/Input.h"
#include "Editor/DragAndDrop.h"


namespace Eclipse::Editor
{
	void print_file_id(const char* path) {
		struct stat s;
		if (stat(path, &s) == 0) {
			LOG(std::to_string((unsigned long)s.st_dev));
			LOG(std::to_string((unsigned long)s.st_ino));
		}
	}

	void AssetWindow::Open()
	{
		flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
		myCurrentPath = ASSET_PATH;
	}

	void AssetWindow::Update()
	{
		using namespace std::filesystem;

		if (Input::GetMouseDown(Keycode::MOUSE_BACK_BUTTON) && !std::filesystem::equivalent(myCurrentPath, ASSET_PATH))
		{
			myCurrentPath = myCurrentPath.parent_path();
		}

		ImGui::BeginChild("FolderStructure", ImVec2(folderStructureWidth, ImGui::GetContentRegionAvail().y), true);

		if (ImGui::TreeNodeEx(ICON_FA_FOLDER " Assets", ImGuiTreeNodeFlags_DrawLinesFull | ImGuiTreeNodeFlags_DrawLinesToNodes | ImGuiTreeNodeFlags_DefaultOpen))
		{
			DrawAssetHiearchy(ASSET_PATH);
			ImGui::TreePop();
		}

		ImGui::EndChild();

		ImGui::SameLine();

		float customWidth = ImGui::GetWindowWidth() - folderStructureWidth + scrollBarWidth;
		ImGui::BeginChild("CustomMenuBarRegion", ImVec2(customWidth, ImGui::GetContentRegionAvail().y), false);

		DrawAssetExplorer(customWidth);

		ImGui::EndChild();
	}

	void AssetWindow::OpenFile(const FileInfo& fifo)
	{
		switch (fifo.type)
		{
		case FileInfo::FileType_Scene: // Open it.
			break;

		default:
			system(fifo.filePath.string().c_str());
			break;
		}
	}

	void AssetWindow::DrawAssetHiearchy(const char* path)
	{
		using namespace std::filesystem;

		static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_DrawLinesFull | ImGuiTreeNodeFlags_DrawLinesToNodes;

		std::vector<directory_entry> entries = GetDirectoryEntries(path, true);


		for (auto& entry : entries)
		{
			if (entry.is_directory())
			{
				if (ImGui::TreeNodeEx((std::string(ICON_FA_FOLDER " ") + entry.path().filename().stem().string()).c_str(), base_flags))
				{
					DrawAssetHiearchy(entry.path().string().c_str());
					ImGui::TreePop();
				}
			}
			else
			{
				FileInfo info = Resources::GetFileInfo(entry);
				//ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
				//ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0, 0, 0));
				//ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0));

				ImGui::Button((std::string(info.GetIcon()) + std::string(" ") + entry.path().filename().stem().string()).c_str());

				//ImGui::PopStyleColor(3);

				std::string relativePath = std::filesystem::relative(entry, SOURCE_PATH).string();

				DragAndDrop::BeginSource(relativePath.c_str(), relativePath.size(), info);

				if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
				{
					Hiearchy_Active_FilePath = entry;
					ImGui::OpenPopup("AssetContextHiearchyMenu");
				}

				CheckFileClicked(entry);
			}
		}

		DrawContextMenu("AssetContextHiearchyMenu", Hiearchy_Active_FilePath);
	}

	void AssetWindow::DrawAssetExplorer(float windowWidth)
	{
		using namespace std::filesystem;

		std::filesystem::path startPath = std::filesystem::relative(myCurrentPath, ASSET_PATH "../");


		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0, 0, 0));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0));

		std::string pathCombiner = ASSET_PATH;
		for (auto& path : startPath)
		{
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
				myCurrentPath = pathCombiner;
			}
		}

		ImGui::Separator();


		float width = windowWidth + ImGui::GetWindowPos().x - scrollBarWidth * 2;
		float buttonSize = 100.0f * myButtonSizeMultiplier;
		float padding = ImGui::GetStyle().ItemSpacing.x;

		for (const directory_entry& entry : GetDirectoryEntries(myCurrentPath, true))
		{
			ImVec2 pos = ImGui::GetCursorPos();

			FileInfo info = Resources::GetFileInfo(entry);
			const char* icon = info.GetIcon();

			ImGui::PushID((std::string("##") + entry.path().string()).c_str());

			ImVec2 buttonSizeVec(buttonSize, buttonSize);

			ImColor col(200, 200, 200, 255);
			if (!Active_FilePath.empty() && std::filesystem::equivalent(Active_FilePath, entry))
			{
				col = ImColor(150, 150, 255, 255);
			}


			ImGui::PushFont(Editor::EditorContext::fontExtraLarge);
			ImGui::PushStyleColor(ImGuiCol_Text, col.Value);
			ImGui::Button(icon, buttonSizeVec);
			ImGui::PopStyleColor();
			ImGui::PopFont();

			std::string relativePath = std::filesystem::relative(entry, SOURCE_PATH).string();

			DragAndDrop::BeginSource(relativePath.c_str(), relativePath.size(), info);

			std::string label = entry.path().filename().string();
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

			if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
			{
				Active_FilePath = entry.path();
				print_file_id(Active_FilePath.string().c_str());
			}
			else if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
			{
				Active_FilePath = entry.path();
				ImGui::OpenPopup("AssetContextMenu");
			}

			CheckFileClicked(entry);

			float currentWidth = ImGui::GetItemRectMax().x;

			if (currentWidth + buttonSize + padding < width)
			{
				ImGui::SameLine();
			}
		}
		ImGui::PopStyleColor(3);

		DrawContextMenu("AssetContextMenu", Active_FilePath);
	}

	void AssetWindow::DrawContextMenu(const std::string& key, std::filesystem::path& aPath)
	{
		if (ImGui::BeginPopup(key.c_str()))
		{
			if (ImGui::MenuItem("Open in file explorer"))
			{
				auto path = aPath.make_preferred().string();
				std::string cmd;

				if (std::filesystem::is_directory(aPath))
					cmd = "explorer \"" + path + "\"";
				else
					cmd = "explorer /select,\"" + path + "\"";

				system(cmd.c_str());
			}

			if (ImGui::MenuItem("Open file"))
			{
				OpenFile(Resources::GetFileInfo(aPath));
			}

			ImGui::EndPopup();
		}
	}

	void AssetWindow::CheckFileClicked(const std::filesystem::path& aPath)
	{
		if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
		{
			if (std::filesystem::is_directory(aPath))
			{
				myCurrentPath = aPath;
			}
			else
			{
				Active_FilePath = aPath;
				OpenFile(Resources::GetFileInfo(aPath));
			}
		}
	}

	std::vector<std::filesystem::directory_entry> AssetWindow::GetDirectoryEntries(const std::filesystem::path& aPath, bool sort)
	{
		using namespace std::filesystem;

		std::vector<directory_entry> entries;
		for (auto entry : directory_iterator(aPath))
		{
			entries.push_back(entry);
		}

		if (!sort) return entries;

		std::sort(entries.begin(), entries.end(),
			[](directory_entry const& a, directory_entry const& b) {
				if (a.is_directory() != b.is_directory())
				{
					return a.is_directory();
				}

				return a.path().filename().string() < b.path().filename().string();
			});

		return entries;
	}

}
#endif