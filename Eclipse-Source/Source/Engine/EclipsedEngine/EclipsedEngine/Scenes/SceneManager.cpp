#include "SceneManager.h"

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"

#include "SceneLoader.h"

#include "CoreEngine/PathManager.h"

#include "PhysicsEngine/PhysicsEngine.h"
#include "GraphicsEngine/RenderCommands/CommandList.h"

#include "EntityEngine/ComponentManager.h"
#include "CoreEngine/Settings/BuildSettings.h"

#include <fstream>
//#include "CoreEngine/Settings/.h"

namespace Eclipse
{
	void SceneManager::LoadScene(const std::string& nameOrPath)
	{
		if (nameOrPath.empty()) return;

		std::string path = nameOrPath;
		if (!std::filesystem::path(nameOrPath).has_extension()) {
			path += ".scene";
		}

		if (std::filesystem::exists(PathManager::GetAssetDir() / path))
		{
			ActiveSceneName = std::filesystem::path(path).filename().stem().string();
		}

		SceneLoader::Load((PathManager::GetAssetDir() / path).generic_string().c_str());
	}

	void SceneManager::LoadScene(unsigned idx)
	{
		if (scenePaths.empty()) return;

		SceneLoader::Load((PathManager::GetAssetDir() / scenePaths[idx]).generic_string().c_str());

		ActiveSceneName = std::filesystem::path(scenePaths[idx]).filename().stem().string();
	}

	void SceneManager::ReloadActiveScene()
	{
		LoadScene(ActiveSceneName);
	}

	void SceneManager::SaveScenes()
	{
	}

	void SceneManager::SaveActiveScene()
	{
		if (ActiveSceneName.empty()) return;

		SceneLoader::Save((PathManager::GetAssetDir() / scenePaths[nameToIdx[ActiveSceneName]]).generic_string().c_str());
	}

	void SceneManager::AddScene(const std::string& aPath)
	{
		std::filesystem::path path = aPath;

		std::string name = path.filename().stem().string();
		nameToIdx[name] = (unsigned)scenePaths.size();
		scenePaths.push_back(aPath);
	}

	void SceneManager::LoadSceneData()
	{
		using namespace rapidjson;

		const std::vector<std::string>& sceneIndex = Settings::BuildSettings::GetSceneIndex();
		if (sceneIndex.empty()) return;

		for (int i = 0; i < sceneIndex.size(); i++)
		{
			nameToIdx[std::filesystem::path(sceneIndex[i]).filename().stem().generic_string()] = i;
			scenePaths.push_back(sceneIndex[i]);
		}
	}

	void SceneManager::SaveSceneData()
	{
		Settings::BuildSettings::SetSceneIndex(scenePaths);
		Settings::BuildSettings::Save();
	}

	void SceneManager::ClearScene()
	{
		ActiveSceneName = "";

		CommandListManager::ResetAllCommandLists();

		ComponentManager::Clear();
		Reflection::ReflectionManager::ClearList();

		PhysicsEngine::CleanUp();
	}

	std::unordered_map<std::string, unsigned>& SceneManager::GetNameToIdx() { return nameToIdx; }
	std::vector<std::string>& SceneManager::GetScenePaths() { return scenePaths; }
	const char* SceneManager::GetActiveScene() { return ActiveSceneName.c_str(); }
}