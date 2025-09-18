#include "AssetWindow.h"

#include "ImGui/imgui.h"
#include "ECS/ComponentManager.h"

#include "Input/Input.h"
#include "Editor/DragAndDrop.h"


namespace Eclipse::Editor
{
	void AssetWindow::Open()
	{
		//flags = ImGuiWindowFlags_MenuBar;
		myCurrentPath = ASSET_PATH;
	}

	void AssetWindow::Update()
	{
		using namespace std::filesystem;

		if (Input::GetMouseDown(Keycode::MOUSE_BACK_BUTTON) && !std::filesystem::equivalent(myCurrentPath, ASSET_PATH))
		{
			myCurrentPath = myCurrentPath.parent_path();
		}

		std::filesystem::path startPath = std::filesystem::relative(myCurrentPath, ASSET_PATH "../");


		float folderStructureWidth = 200.f;
		float scrollBarWidth = 15.f;

		ImGui::BeginChild("FolderStructure", ImVec2(folderStructureWidth, ImGui::GetWindowHeight()), true, ImGuiWindowFlags_NoScrollbar);
		ImGui::Text("Welcome! You are here early.");
		ImGui::Text("You idiot.  " ICON_FA_HAND_MIDDLE_FINGER);
		ImGui::EndChild();

		ImGui::SameLine();

		float customWidth = ImGui::GetWindowWidth() - folderStructureWidth + scrollBarWidth;
		ImGui::BeginChild("CustomMenuBarRegion", ImVec2(customWidth, ImGui::GetWindowHeight()), false, ImGuiWindowFlags_NoScrollbar);

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
			}

			ImGui::SameLine();

			if (ImGui::Button(path.string().c_str()))
			{
				myCurrentPath = pathCombiner;
			}
		}

		ImGui::Separator();


		float width = customWidth + ImGui::GetWindowPos().x - scrollBarWidth * 2;
		float buttonSize = 100.0f * myButtonSizeMultiplier;
		float padding = ImGui::GetStyle().ItemSpacing.x;

		for (const directory_entry& entry : directory_iterator(myCurrentPath))
		{
			ImVec2 pos = ImGui::GetCursorPos();

			FileInfo info = Resources::GetFileInfo(entry);
			const char* icon = info.GetIcon();

			ImGui::PushID(Random::GetValue<int>());

			ImVec2 buttonSizeVec(buttonSize, buttonSize);
			if (ImGui::Button((std::string("##dirButton") + entry.path().string()).c_str(), buttonSizeVec))
			{
				LOG_ERROR("Not implemented: Must make assets selectable.");
			}

			ImColor col(200, 200, 200, 255);
			if (!Active_FilePath.empty() && std::filesystem::equivalent(Active_FilePath, entry))
			{
				col = ImColor(150, 150, 255, 255);
			}

			ImVec2 min = ImGui::GetItemRectMin();
			ImVec2 max = ImGui::GetItemRectMax();
			ImVec2 center = ImVec2((min.x + max.x) * 0.5f, (min.y + max.y) * 0.5f);

			ImGui::PushFont(Editor::EditorContext::fontExtraLarge);
			ImVec2 iconSize = ImGui::CalcTextSize(icon);
			ImGui::GetWindowDrawList()->AddText(
				Editor::EditorContext::fontExtraLarge,
				0.0f,
				ImVec2(center.x - iconSize.x * 0.5f, min.y + 6),
				col,
				icon
			);
			ImGui::PopFont();

			std::string label = entry.path().filename().string();
			const float maxSize = buttonSize - 86.f;
			if (label.size() > maxSize)
			{
				label.erase(maxSize, label.size());
				label += "...";
			}

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

			if(ImGui::IsItemClicked(ImGuiMouseButton_Left))
			{
				Active_FilePath = entry.path();
			}
			else if (ImGui::IsItemClicked(ImGuiMouseButton_Right))
			{
				Active_FilePath = entry.path();
				ImGui::OpenPopup("AssetContextMenu");
			}
			


			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				if (entry.is_directory())
				{
					myCurrentPath = entry.path();
				}
				else
				{
					Active_FilePath = entry.path();
					OpenFile(info);
				}
			}

			float currentWidth = ImGui::GetItemRectMax().x;

			if (currentWidth + buttonSize + padding < width)

			{
				ImGui::SameLine();
			}
		}
		ImGui::PopStyleColor(3);

		if (ImGui::BeginPopup("AssetContextMenu"))
		{
			if (ImGui::MenuItem("Open in file explorer"))
			{
				auto path = Active_FilePath.make_preferred().string();
				std::string cmd;

				if (std::filesystem::is_directory(Active_FilePath))
					cmd = "explorer \"" + path + "\"";
				else
					cmd = "explorer /select,\"" + path + "\"";

				system(cmd.c_str());
			}

			ImGui::EndPopup();
		}

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
}