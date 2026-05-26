#pragma once

#ifdef ECLIPSED_EDITOR

#include "EclipsedEngine/Editor/Windows/WindowTypes/Settings/BuildSettingsWindow.h"
#include "EclipsedEngine/Editor/Game/GameCompiler.h"
#include "CoreEngine/PathManager.h"
#include "AssetEngine/AssetManager.h"

namespace Eclipse::Editor
{
	void BuildSettingsWindow::Update()
	{
		ImGui::Text("Debug");
		ImGui::SameLine();
		ImGui::Checkbox("##is_debug_build", &isDebugBuild);

		ImGui::Spacing();

		ImGui::Text("Enable Networking");
		ImGui::SameLine();
		ImGui::Checkbox("##has-networking-enabled-in-build", &enableNetworking);

		ImGui::Separator();

		if (ImGui::Button("Build"))
			Build();

	}

	void BuildSettingsWindow::Build()
	{
		std::filesystem::remove_all(PathManager::GetProjectRoot() / "Build");
		std::filesystem::create_directory(PathManager::GetProjectRoot() / "Build");

		Assets::AssetManager::PackAssets();

		BatchScript script(
			PathManager::GetEngineRoot().parent_path() / "Tools",
			"build-game-editor.bat",
			{
				"-DPROJECT_PATH=" + PathManager::GetProjectRoot().generic_string(),
				"-DENGINE_PATH=" + PathManager::GetEngineRoot().parent_path().generic_string(),
				"-DCONFIG=" + std::string(isDebugBuild ? "Debug" : "Release"),
				"-DENABLE_NETWORKING=" + std::string(isDebugBuild ? "Debug" : "Release")
			}
		);

		script.Run(true);
	}
}

#endif