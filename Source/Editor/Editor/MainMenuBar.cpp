#include "MainMenuBar.h"

#include "ImGui/imgui.h"

namespace Eclipse::Editor
{
	void MainMenuBar::Init()
	{

	}

	void MainMenuBar::Update()
	{
		ImGui::BeginMainMenuBar();

		DrawViews();

		ImGui::EndMainMenuBar();
	}

	void MainMenuBar::DrawViews()
	{
		if (ImGui::BeginMenu("Views"))
		{
			ImGui::EndMenu();
		}
	}
}