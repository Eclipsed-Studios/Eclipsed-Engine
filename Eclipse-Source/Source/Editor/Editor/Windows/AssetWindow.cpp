#ifdef _EDITOR
#include "AssetWindow.h"

#include "ImGui/imgui.h"
#include "ECS/ComponentManager.h"

#include "Input/Input.h"
#include "Editor/DragAndDrop.h"
#include "Editor/TextureIconManager.h"

#include "Scenes/SceneManager.h"


namespace Eclipse::Editor
{
	void AssetWindow::Open()
	{
		//dirTree = Utilities::DirectoryTree(ASSET_PATH);
		//Active_Path = &dirTree.GetDirectoryFromPath(ASSET_PATH)->path;

		//activeDir = dirTree.GetDirectoryFromPath(Active_Path->filePath);

		//FileWatcher::Subscribe(ASSET_PATH, [this](const FileWatcherEvent& e) {HandleFileChanges(e);});

		flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
	}

	void AssetWindow::Update()
	{
		/*using namespace std::filesystem;

		if (Input::GetMouseDown(Keycode::MOUSE_BACK_BUTTON))
		{
			activeDir = dirTree.GetDirectoryFromPath(Active_Path->filePath.parent_path());
			Active_Path = &dirTree.GetDirectoryFromPath(activeDir->path.filePath)->path;
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

		ImGui::EndChild();*/
	}



	void AssetWindow::DrawAssetHiearchy(const char* path)
	{
		//using namespace std::filesystem;

		//static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_DrawLinesFull | ImGuiTreeNodeFlags_DrawLinesToNodes;

		//

		//ImGui::Text("I dont have the energy to");
		//ImGui::Text("fix this recursive");
		//ImGui::Text("piece of shit.");
		//ImGui::Text(ICON_FA_HAND_MIDDLE_FINGER);


		////std::vector<directory_entry> entries = GetDirectoryEntries(path, true);


		////for (auto& entry : entries)
		////{
		////	if (entry.is_directory())
		////	{
		////		if (ImGui::TreeNodeEx((std::string(ICON_FA_FOLDER " ") + entry.path().filename().stem().string()).c_str(), base_flags))
		////		{
		////			DrawAssetHiearchy(entry.path().string().c_str());
		////			ImGui::TreePop();
		////		}
		////	}
		////	else
		////	{
		////		FileInfo info = Resources::GetFileInfo(entry);
		////		//ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
		////		//ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0, 0, 0));
		////		//ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0));

		////		ImGui::Button((std::string(info.GetIcon()) + std::string(" ") + entry.path().filename().stem().string()).c_str());

		////		//ImGui::PopStyleColor(3);

		////		std::string relativePath = std::filesystem::relative(entry, SOURCE_PATH).string();

		////		DragAndDrop::BeginSource(relativePath.c_str(), relativePath.size(), info);

		////		if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
		////		{
		////			Hiearchy_Active_FilePath = entry;
		////			ImGui::OpenPopup("AssetContextHiearchyMenu");
		////		}

		////		CheckFileClicked(entry);
		////	}
		////}

		//DrawContextMenu("AssetContextHiearchyMenu", Active_Path->relativeFilePath);
	}

	void AssetWindow::DrawAssetExplorer(float width)
	{
		/*namespace fs = std::filesystem;

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0, 0, 0));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0));

		std::string pathCombiner = ASSET_PATH;
		for (auto& path : activeDir->path.relativeFilePath)
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
				fs::path wantedPath(pathCombiner);

				fs::path current = fs::weakly_canonical(activeDir->path.filePath);
				fs::path wanted = fs::weakly_canonical(wantedPath);

				while (current != wanted)
				{
					current = fs::weakly_canonical(current.parent_path());
				} 

				activeDir = dirTree.GetDirectoryFromPath(current);
			}
		}


		ImGui::Separator();

		if (!activeDir->subDirectories.empty())
		{
			for (std::shared_ptr<Utilities::Directory>& dir : activeDir->subDirectories)
			{
				DirectoryEntry(width, dir.get());
			}
		}

		if (!activeDir->files.empty())
		{
			for (Utilities::FileInfo& file : activeDir->files)
			{
				AssetEntry(width, file);
			}
		}

		ImGui::PopStyleColor(3);*/
	}













	void AssetWindow::DrawContextMenu(const std::string& key, std::filesystem::path& aPath)
	{
		/*if (ImGui::BeginPopup(key.c_str()))
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
				OpenFile(Utilities::FileInfo::GetFileInfo(aPath));
			}


			if (ImGui::BeginMenu("Create"))
			{
				if (ImGui::MenuItem("Scene"))
				{

				}

				ImGui::EndMenu();
			}

			ImGui::EndPopup();
		}*/
	}

	bool AssetWindow::CheckFileClicked()
	{
		/*if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
		{
			return true;
		}
		*/
		return false;
	}

	void AssetWindow::DrawExplorerEntry(float windowWidth, const Utilities::FileInfo& file)
	{
		/*const float width = windowWidth + ImGui::GetWindowPos().x - scrollBarWidth * 2;
		const float buttonSize = 100.0f * myButtonSizeMultiplier;
		const float padding = ImGui::GetStyle().ItemSpacing.x;


		ImVec2 pos = ImGui::GetCursorPos();

		const char* icon = file.GetIcon();

		ImGui::PushID((std::string("##") + file.filePath.string()).c_str());

		ImVec2 buttonSizeVec(buttonSize, buttonSize);

		ImColor col(200, 200, 200, 255);
		if (!Active_FilePath.empty() && std::filesystem::equivalent(Active_FilePath, file.filePath))
		{
			col = ImColor(150, 150, 255, 255);
		}


		ImGui::PushFont(Editor::EditorContext::fontExtraLarge);
		ImGui::PushStyleColor(ImGuiCol_Text, col.Value);

		if (file.type == Utilities::FileInfo::FileType_Texture)
		{
			const IconData& data = IconManager::GetIcon(file);

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

		DragAndDrop::BeginSource(file.relativeFilePath.string().c_str(), file.relativeFilePath.string().size(), file);

		std::string label = file.filePath.filename().string();
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
			Active_FilePath = file.filePath;
			InspectorWindow::activeType = ActiveItemTypes_Asset;
		}
		else if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
		{
			Active_FilePath = file.filePath;
			ImGui::OpenPopup("AssetContextMenu");
		}

		float currentWidth = ImGui::GetItemRectMax().x;

		if (currentWidth + buttonSize + padding < width)
		{
			ImGui::SameLine();
		}*/
	}

	void AssetWindow::AssetEntry(float windowWidth, const Utilities::FileInfo& file)
	{
		/*DrawExplorerEntry(windowWidth, file);

		if (CheckFileClicked())
		{
			Active_FilePath = file.filePath;
			OpenFile(Utilities::FileInfo::GetFileInfo(std::string(ASSET_PATH) + file.relativeFilePath.generic_string()));
		}*/
	}

	void AssetWindow::DirectoryEntry(float windowWidth, Utilities::FileNode* directory)
	{
		/*DrawExplorerEntry(windowWidth, directory->path);

		if (CheckFileClicked())
		{
			Active_Path = &directory->path;

			activeDir = dirTree.GetDirectoryFromPath(Active_Path->filePath);
		}*/
	}


	void AssetWindow::OpenFile(const Utilities::FileInfo& fifo)
	{
		/*switch (fifo.type)
		{
		case Utilities::FileInfo::FileType_Scene:
			SceneManager::LoadScene(fifo.filePath.string());
			break;

		default:
			system(fifo.filePath.string().c_str());
			break;
		}*/
	}

	void AssetWindow::HandleFileChanges(const FileWatcherEvent& event)
	{
		//namespace fs = std::filesystem;

		//switch ((int)event.action)
		//{
		//case FILE_ACTION_MODIFIED: {
		//	LOG_WARNING("Asset Event Modified not implemented.");
		//} break;

		//case FILE_ACTION_ADDED: {
		//	fs::path path(event.path);

		//	const std::string sPath = path.parent_path().generic_string();
		//	if (directoryPathToFileList.find(sPath) == directoryPathToFileList.end()) return;

		//	std::vector<FileInfo>& fileList = directoryPathToFileList[sPath];

		//	FileInfo info = Resources::GetFileInfo(event.path);
		//	info.relativeFilePath = std::filesystem::relative(info.filePath, SOURCE_PATH).string();

		//	fileList.push_back(info);


		//	std::sort(fileList.begin(), fileList.end(),
		//		[](FileInfo const& a, FileInfo const& b) {
		//			if (a.type == FileInfo::FileStatus_Directory)
		//			{
		//				return true;
		//			}

		//			return a.filePath.filename().string() < b.filePath.filename().string();
		//		});
		//} break;

		//case FILE_ACTION_REMOVED: {
		//	fs::path path(event.path);
		//	std::vector<FileInfo>& fileList = directoryPathToFileList[path.parent_path().lexically_normal().generic_string()];

		//	for (auto it = fileList.begin(); it != fileList.end();)
		//	{
		//		if (it->filePath == event.path)
		//		{
		//			fileList.erase(it);
		//			return;
		//		}
		//		it++;
		//	}
		//} break;

		//case FILE_ACTION_RENAMED_NEW_NAME: {
		//	// Dont do anything unless its an image.
		//} break;

		//case FILE_ACTION_RENAMED_OLD_NAME: {

		//} break;
		//}
	}
}
#endif