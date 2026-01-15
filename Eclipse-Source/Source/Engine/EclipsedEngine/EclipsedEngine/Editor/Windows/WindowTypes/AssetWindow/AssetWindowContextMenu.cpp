#include "AssetWindowContextMenu.h"

#include "AssetEngine/AssetFactory.h"

#include <filesystem>
#include "ImGui/imgui.h"

#include "CoreEngine/Debug/DebugLogger.h"
#include "CoreEngine/PathManager.h"

#include <fstream>

namespace Eclipse::Editor
{
	AssetWindowContextMenu::AssetWindowContextMenu() : AbstractContextMenu("AssetsCtxMenu") {}

	void AssetWindowContextMenu::SetActivePath(const std::filesystem::path& aPath)
	{
		activePath = aPath;
	}

	void AssetWindowContextMenu::UpdateAlways()
	{
		if (Renaming)
		{
			ImGui::Begin("Rename", (bool*)1, ImGuiWindowFlags_AlwaysAutoResize);

			ImGui::InputText("New name", tempName, 512);


			if (ImGui::Button("OK"))
			{
				std::string renamePathExt = activePathAtRenaming.extension().string();

				memcpy(tempName + strlen(tempName), renamePathExt.c_str(), renamePathExt.size() + 1);

				std::filesystem::path newName = activePathAtRenaming.parent_path() / tempName;

				std::filesystem::rename(activePathAtRenaming, newName);
				Renaming = false;
			}

			ImGui::End();
		}
	}

	void AssetWindowContextMenu::Update()
	{
		if (ImGui::BeginMenu("Create"))
		{
			CreateMenu();
			ImGui::EndMenu();
		}

		if (ImGui::MenuItem("Show in Explorer"))
		{
			LOG_ERROR("Show in Explorer not implemented.");
		}

		if (activePath.empty()) ImGui::BeginDisabled();

		if (ImGui::MenuItem("Rename"))
		{
			activePathAtRenaming = activePath;
			std::string str = activePathAtRenaming.filename().replace_extension().string();
			memcpy(tempName, str.c_str(), str.size() + 1);

			Renaming = true;
		}

		if (ImGui::MenuItem("Open"))
		{
			LOG_ERROR("Open not implemented.");
		}

		if (ImGui::MenuItem("Delete"))
		{
			LOG_ERROR("Delete not implemented.");
		}

		if (activePath.empty()) ImGui::EndDisabled();

		if (ImGui::MenuItem("Copy Path"))
		{
			LOG_ERROR("Copy Path not implemented.");
		}
	}

	void AssetWindowContextMenu::CreateMenu()
	{
		if (ImGui::MenuItem("Folder"))
		{
			std::filesystem::create_directory(PathManager::GetAssetDir() / activePath / "NewFolder");
		}

		if (ImGui::MenuItem("Material"))
		{
			auto path = (PathManager::GetAssetDir() / "Test.mat").generic_string();
			Assets::AssetFactory::CreateMaterial(path.c_str());
		}

		if (ImGui::MenuItem("Component"))
		{
			LOG_ERROR("Creating Component not implemented.");
		}

		if (ImGui::MenuItem("Scene"))
		{
			std::ofstream outputStream(PathManager::GetAssetDir() / activePath / "NewScene.scene");
			outputStream.close();
		}

		if (ImGui::MenuItem("Physics Material"))
		{
			LOG_ERROR("Creating Physics Material not implemented.");
		}

		//if (ImGui::MenuItem("Prefab"))
		//{
		//	std::ofstream outputStream(PathManager::GetAssetDir()/activePath/"New prefab.eprf");

		//	outputStream << "Test";
		//	outputStream.close();

		//}
	}
}