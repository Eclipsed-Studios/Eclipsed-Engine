#include "WindowManager.h"

#include "ImGui/imgui.h"

#include "Timer.h"

#include "Debug/DebugInformationCollector.h"

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

			ImGui::SameLine(ImGui::GetWindowWidth() - (ImGui::CalcTextSize("Debug").x * 2) + 10);
			if (ImGui::Button("Debug"))
			{
				myShowDebugWindow = !myShowDebugWindow;
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

		if (myShowDebugWindow)
		{
			DrawDebugInfoWindow();
		}
	}

	void WindowManager::DrawDebugInfoWindow()
	{
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 work_pos = viewport->WorkPos;
		ImVec2 work_size = viewport->WorkSize;
		ImVec2 window_pos = ImVec2(work_pos.x + work_size.x, work_pos.y + work_size.y);
		ImVec2 window_pos_pivot = ImVec2(1.0f, 1.0f);

		ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);

		ImGui::SetNextWindowBgAlpha(0.35f);

		ImGui::Begin("PerfTooltip", &myShowDebugWindow,
			ImGuiWindowFlags_NoDecoration |
			ImGuiWindowFlags_AlwaysAutoResize |
			ImGuiWindowFlags_NoSavedSettings |
			ImGuiWindowFlags_NoFocusOnAppearing |
			ImGuiWindowFlags_NoNav);

		float fps = ImGui::GetIO().Framerate;
		float totalTime = Time::GetTotalTime();
		int renderCalls = DebugInformationCollector::GetRenderCalls();

		ImGui::Text("Render Calls: %d", renderCalls);
		ImGui::Text("FPS: %.1f", fps);
		ImGui::Text("Total Time: %.1f", totalTime);

		ImGui::End();
	}
}