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

		script.Run();
	}

	void GameModuleManager::CompileAndLoad()
	{
		const char* activeScene = SceneManager::GetActiveScene();
		SceneManager::UnloadScene();

		GameLoader::UnloadGameDLL();

		std::filesystem::remove(PathManager::GetGameDllBuildPath() / "Game.dll");
		std::filesystem::remove(PathManager::GetGameDllBuildPath() / "Game.pdb");

		GenerateGameEditor();
		Compile();

		GameLoader::LoadGameDLL();

		SceneManager::LoadScene(activeScene);
	}
}