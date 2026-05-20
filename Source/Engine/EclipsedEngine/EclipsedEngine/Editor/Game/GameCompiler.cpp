#include "GameCompiler.h"

#include "CoreEngine/PathManager.h"
#include "GameLoader.h"
#include <filesystem>

#include "EclipsedEngine/Scenes/SceneManager.h"

namespace Eclipse
{
	void GameModuleManager::GenerateGameEditor()
	{
		static BatchScript script(
			PathManager::GetProjectRoot() / "Tools",
			"generate-game-editor.bat",
			{
				PathManager::GetProjectRoot().generic_string(),
				PathManager::GetEngineRoot().parent_path().generic_string()
			}
		);

		script.Run();
	}

	void GameModuleManager::Compile()
	{
		static BatchScript script(
			PathManager::GetProjectRoot() / "Tools",
			"build-game-dll.bat"
		);

		script.Run(true);
	}

	void GameModuleManager::CompileAndLoad()
	{
		static std::string supportedExtensions[] = {
			".hpp",
			".cpp",
			".h",
			".inl"
		};

		bool wasChanged = false;
		if (std::filesystem::exists(PathManager::GetGameDllBuildPath() / "Game.dll"))
		{
			auto lastWriteTime = std::filesystem::last_write_time(PathManager::GetGameDllBuildPath() / "Game.dll");

			for (const std::filesystem::directory_entry& dir : std::filesystem::recursive_directory_iterator(PathManager::GetAssetsPath()))
			{
				for (const std::string& extension : supportedExtensions)
				{
					if (dir.path().extension() == extension)
					{
						auto fileWriteTime = std::filesystem::last_write_time(dir.path());

						if (fileWriteTime > lastWriteTime)
						{
							wasChanged = true;
						}
					}
				}
			}
		}
		else
		{
			wasChanged = true;
		}


		if (wasChanged)
		{
			const char* activeScene = SceneManager::GetActiveScene();
			SceneManager::UnloadScene();

			GameLoader::UnloadGameDLL();

			std::filesystem::remove(PathManager::GetGameDllBuildPath() / "Game.dll");
			std::filesystem::remove(PathManager::GetGameDllBuildPath() / "Game.pdb");

			GenerateGameEditor();
			Compile();

			GameLoader::LoadGameDLL();

			//SceneManager::LoadScene(activeScene);
		}
		else
		{
			GameLoader::UnloadGameDLL();
			GameLoader::LoadGameDLL();
		}
	}
}