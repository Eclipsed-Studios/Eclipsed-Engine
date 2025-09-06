#include "AssetWindow.h"

#include "ImGui/imgui.h"
#include "ECS/ComponentManager.h"

#include "Input/Input.h"


namespace ENGINE_NAMESPACE::Editor
{
	AssetWindow::AssetWindow(const int& aId)
	{
		myWindowName = "Assets";
		myID = aId == -1 ? Random::GetValue<int>() : aId;

		myCurrentPath = ASSET_PATH;

        flags = ImGuiWindowFlags_MenuBar;
	}

	void AssetWindow::Open()
	{
	}
	
    void AssetWindow::Update()
    {
        using namespace std::filesystem;

        if (Input::GetMouseDown(MouseButton::BACK_BUTTON) && myCurrentPath != ASSET_PATH)
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
            bool buttonPressed = ImGui::Button(entry.path().filename().string().c_str(), { buttonSize, buttonSize });

            if (entry.is_directory() && buttonPressed)
            {
                myCurrentPath = entry.path();
            }
            else if (buttonPressed)
            {
                Active_FilePath = entry.path();
            }

            float currentWidth = ImGui::GetItemRectMax().x;

            if (currentWidth + buttonSize + padding < width)

            {
                ImGui::SameLine();
            }
        }
    }

	
	void AssetWindow::Close()
	{
	}
}