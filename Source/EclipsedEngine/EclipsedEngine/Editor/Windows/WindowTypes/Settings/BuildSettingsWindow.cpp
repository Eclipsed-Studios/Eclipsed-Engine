#pragma once

#ifdef ECL_EDITOR

#include "EclipsedEngine/Editor/Windows/WindowTypes/Settings/BuildSettingsWindow.h"
#include "EclipsedEngine/Editor/Game/GameCompiler.h"
#include "Core/PathManager.h"
#include "Assets/AssetManager.h"

#include "Core/Settings/BuildSettings.h"

namespace Eclipse::Editor
{
	void BuildSettingsWindow::Update()
	{
		Settings::BuildSettings::Data& data = Settings::BuildSettings::GetData();

		ImGui::Text("Enable Steam SDK");
		ImGui::SameLine();
		ImGui::Checkbox("##has-steam-api-enabled", &data.enableSteamSdk);

		ImGui::Spacing();

		ImGui::Text("Enable Discord SDK");
		ImGui::SameLine();
		ImGui::Checkbox("##has-discord-api-enabled", &data.enableDiscordSdk);

			ImGui::Spacing();
		ImGui::Spacing();

		ImGui::Text("Enable Networking");
		ImGui::SameLine();
		ImGui::Checkbox("##has-networking-enabled-in-build", &data.enableNetworking);

		ImGui::Separator();

		if (ImGui::Button("Clean Build"))
			CleanBuild();

		ImGui::SameLine();

		{
			if (ImGui::Button("Package Assets"))
				CookAssets();

			if (ImGui::BeginItemTooltip())
			{
				ImGui::Text("Cooks and exports assets.");
				ImGui::EndTooltip();
			}
		}

		ImGui::SameLine();

		{
			if (ImGui::Button("Build"))
				Build();

			if (ImGui::BeginItemTooltip())
			{
				ImGui::Text("Just builds the executable.");
				ImGui::EndTooltip();
			}
		}

	}

	void BuildSettingsWindow::CookAssets()
	{
		Assets::AssetManager::CookAndPackageAssets();
	}

	void BuildSettingsWindow::CleanBuild()
	{
		Settings::BuildSettings::Data& data = Settings::BuildSettings::GetData();

		std::filesystem::remove_all(PathManager::GetProjectRoot() / "Build");
		std::filesystem::create_directory(PathManager::GetProjectRoot() / "Build");

		Assets::AssetManager::CookAndPackageAssets();

		BatchScript script(
			PathManager::GetEngineRoot().parent_path() / "Tools",
			"build-game-editor.bat",
			{
				"\"PROJECT_PATH=" + PathManager::GetProjectRoot().generic_string() + "\"",
				"\"ENGINE_PATH=" + PathManager::GetEngineRoot().parent_path().generic_string() + "\"",
				"\"CONFIG=" + std::string(isDebugBuild ? "Debug" : "Release") + "\"",
				"\"ENABLE_NETWORKING=" + std::string(data.enableNetworking ? "ON" : "OFF") + "\"",
				"\"ENABLE_STEAM_SDK=" + std::string(data.enableSteamSdk ? "ON" : "OFF") + "\"",
				"\"ENABLE_DISCORD_SDK=" + std::string(data.enableDiscordSdk ? "ON" : "OFF") + "\""
			}
		);

		script.Run(true);
	}

	void BuildSettingsWindow::Build()
	{
		Settings::BuildSettings::Data& data = Settings::BuildSettings::GetData();

		BatchScript script(
			PathManager::GetEngineRoot().parent_path() / "Tools",
			"build-game-editor.bat",
			{
				"\"PROJECT_PATH=" + PathManager::GetProjectRoot().generic_string() + "\"",
				"\"ENGINE_PATH=" + PathManager::GetEngineRoot().parent_path().generic_string() + "\"",
				"\"CONFIG=" + std::string(isDebugBuild ? "Debug" : "Release") + "\"",
				"\"ENABLE_NETWORKING=" + std::string(data.enableNetworking ? "ON" : "OFF") + "\"",
				"\"ENABLE_STEAM_SDK=" + std::string(data.enableSteamSdk ? "ON" : "OFF") + "\"",
				"\"ENABLE_DISCORD_SDK=" + std::string(data.enableDiscordSdk ? "ON" : "OFF") + "\""
			}
		);

		script.Run(true);
	}
}

#endif