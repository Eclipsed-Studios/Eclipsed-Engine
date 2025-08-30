#include "WindowManager.h"

#include "ImGui/imgui.h"


namespace ENGINE_NAMESPACE::Editor
{
	void WindowManager::UpdateMainMenuBar()
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Windows"))
			{
				if (ImGui::MenuItem("Console")) OpenWindow<ConsoleWindow>(-1);

				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Settings"))
			{
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	}

	void WindowManager::Update()
	{
		UpdateMainMenuBar();

		for (auto it = IdToWindow.begin(); it != IdToWindow.end(); )
		{
			const int& id = it->first;
			AbstractWindow* window = it->second;

			if (window->myWasLastOpen != window->myIsOpen)
			{
				delete window;
				it = IdToWindow.erase(it);
			}
			else
			{
				std::string imguiWindowName = window->GetWindowName() + "##" + std::to_string(id);
				ImGui::Begin(imguiWindowName.c_str(), &window->myIsOpen, 0);
				window->Update();
				ImGui::End();

				++it;
			}
		}
	}
}