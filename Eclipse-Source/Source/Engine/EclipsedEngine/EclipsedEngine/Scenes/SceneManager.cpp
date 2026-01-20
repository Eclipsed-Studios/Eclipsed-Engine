#include "SceneManager.h"

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"

#include "SceneLoader.h"

#include "CoreEngine/PathManager.h"

#include "PhysicsEngine/PhysicsEngine.h"
#include "GraphicsEngine/RenderCommands/CommandList.h"

#include "EntityEngine/ComponentManager.h"

#include <fstream>
//#include "CoreEngine/Settings/.h"

namespace Eclipse
{
	void SceneManager::LoadScene(const std::string& nameOrPath)
	{
		if (nameOrPath.empty()) return;

		if (std::filesystem::exists(nameOrPath))
		{
			ActiveSceneName = std::filesystem::path(nameOrPath).filename().stem().string();
		}

		SceneLoader::Load((PathManager::GetAssetDir() / scenePaths[nameToIdx[ActiveSceneName]]).generic_string().c_str());
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

		//std::vector<std::string> names = Settings::SettingsRegistry::Get<std::vector<std::string>>("build.sceneNames");
		//if (names.empty()) return;

		//std::vector<std::string> paths = Settings::SettingsRegistry::Get<std::vector<std::string>>("build.sceneRelativePaths");

		//for (int i = 0; i < names.size(); i++)
		//{
		//	nameToIdx[names[i]] = i;
		//	scenePaths.push_back(paths[i]);
		//}



		//auto paths = PathManager::GetEngineLocal() / "EngineSettings.json";

		//std::ifstream in(paths);

		//std::string jsonString((std::istreambuf_iterator<char>(in)),
		//	std::istreambuf_iterator<char>());

		//in.close();

		//Document d;
		//if (!jsonString.empty())
		//{
		//	d.Parse(jsonString.c_str());
		//}

		//Document::AllocatorType& alloc = d.GetAllocator();

		//if (d.HasMember("scenes"))
		//{
		//	Value& val = d["scenes"].GetArray();

		//	scenePaths.resize(val.Size());

		//	for (SizeType i = 0; i < val.Size(); i++)
		//	{
		//		const Value& sceneObj = val[i];

		//		std::string name = sceneObj["name"].GetString();
		//		std::string relativePath = sceneObj["relativePath"].GetString();
		//		int idx = sceneObj["idx"].GetInt();

		//		nameToIdx[name] = idx;

		//		if (scenePaths.empty()) scenePaths.push_back(relativePath);
		//		else scenePaths[idx] = relativePath;
		//	}
		//}
	}

	void SceneManager::SaveSceneData()
	{
		//std::vector<std::string>& names = Settings::SettingsRegistry::Get<std::vector<std::string>>("build.sceneNames");
		//std::vector<std::string>& paths = Settings::SettingsRegistry::Get<std::vector<std::string>>("build.sceneRelativePaths");

		//names.clear();
		//paths.clear();

		//for (auto& [name, idx] : nameToIdx)
		//{
		//	names.push_back(name);
		//	paths.push_back(scenePaths[idx]);
		//}
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