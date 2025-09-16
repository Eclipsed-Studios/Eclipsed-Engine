#include "AssetWindow.h"

#include "ImGui/imgui.h"
#include "ECS/ComponentManager.h"

#include "Input/Input.h"
#include "Editor/DragAndDrop.h"


namespace Eclipse::Editor
{
	void AssetWindow::Open()
	{
		flags = ImGuiWindowFlags_MenuBar;
		myCurrentPath = ASSET_PATH;
	}

	void AssetWindow::Update()
	{
		using namespace std::filesystem;

		if (Input::GetMouseDown(Keycode::MOUSE_BACK_BUTTON) && myCurrentPath != ASSET_PATH)
		{
			myCurrentPath = myCurrentPath.parent_path();
		}

		if (ImGui::BeginMenuBar())
		{
			float offset = ImGui::GetContentRegionAvail().x - 200;
			if (offset > 0)
			{
				ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offset);
			}

			ImGui::SetNextItemWidth(200);
			ImGui::SliderFloat("##MULTIPLIERS", &myButtonSizeMultiplier, 0.1f, 2.f);

			ImGui::EndMenuBar();
		}

		float width = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;
		float buttonSize = 100.0f * myButtonSizeMultiplier;
		float padding = ImGui::GetStyle().ItemSpacing.x;



		for (const directory_entry& entry : directory_iterator(myCurrentPath))
		{
			ImGui::PushFont(Editor::EditorContext::fontExtraLarge);

			if (entry.is_directory())
			{
				if (ImGui::Button((std::string(ICON_FA_FOLDER "##") + entry.path().string()).c_str(), ImVec2(buttonSize, buttonSize)))
				{
					Active_FilePath = entry.path();
				}
			}
			else
			{
				ImGui::PushFont(Editor::EditorContext::fontTiny);
				if (ImGui::Button(entry.path().filename().stem().string().c_str(), ImVec2(buttonSize, buttonSize)))
				{
					Active_FilePath = entry.path();
				}
				ImGui::PopFont();
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
				}
			}

			ImGui::PopFont();

			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
			{
				myPayloadStr = entry.path().string();
				std::string extension = entry.path().extension().string();

				DragAndDrop::AssetDragAndDropIdx idx = DragAndDrop::supportedFileTypes.at(extension);

				const char* dnd = DragAndDrop::dragAndDropString[(int)idx];

				ImGui::SetDragDropPayload(dnd, myPayloadStr.c_str(), myPayloadStr.size() + 1);

				ImGui::Text(myPayloadStr.c_str());
				ImGui::EndDragDropSource();
			}

			float currentWidth = ImGui::GetItemRectMax().x;

			if (currentWidth + buttonSize + padding < width)

			{
				ImGui::SameLine();
			}
		}
	}
}