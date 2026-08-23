#include "SceneManager.h"

#include "rapidjson/document.h"

#include "SceneLoader.h"

#include "Core/PathManager.h"

#include "Physics/PhysicsEngine.h"
#include "Renderer/RenderCommands/CommandList.h"

#include "ECS/ComponentManager.h"
#include "Core/Settings/BuildSettings.h"
#include "Core/Settings/EditorSettings.h"

#include "EclipsedEngine/DebugLogger.h"

#include "Assets/AssetManager.h"
#include "Assets/Core/AssetDatabase.h"

#include "EclipsedEngine/Reflection/Reflection.h"

namespace Eclipse
{
	SceneRegistry SceneManager::registry;

	void SceneManager::Initialize()
	{
		registry = {};
	}

	void SceneManager::LoadScene(const std::string& name)
	{
		if (name.empty())
			throw std::runtime_error("The scene name tried to load was empty");

		SetActiveSceneType(Default);

		const SceneEntry& entry = registry.GetScene(name);
		LoadScene(entry.guid);
	}

	void SceneManager::LoadScene(const Assets::Scene& scene)
	{
		if (!scene.IsValid())
			throw std::runtime_error("The scene is not valid.");

		std::string name = MainSingleton::GetInstance<Assets::AssetDatabase>().GetProcessedFile(scene.GetAssetID()).fileName;
		SetActiveScene(name.c_str());

		activeScene = scene;
		SceneManager::SetActiveSceneType(SceneManager::Default);
		SceneLoader::Load(scene);
	}

	void SceneManager::LoadScene(Assets::GUID guid)
	{
		Assets::Scene scene = Assets::AssetManager::Load<Assets::Scene>(guid);
		activeSceneGuid = guid;
		LoadScene(scene);
	}

	void SceneManager::UnloadScene()
	{
		SceneLoader::UnloadScene();
	}

	void SceneManager::ReloadActiveScene()
	{
		activeSceneGuid = activeScene.GetAssetID();
		activeScene = Assets::AssetManager::Load<Assets::Scene>(activeScene.GetAssetID());
		LoadScene(activeScene);
	}

	void SceneManager::SaveScenes()
	{
	}

	void SceneManager::SaveActiveScene()
	{
		if (!activeScene.IsValid()) return;
		if (activeScene.GetAssetID() == Assets::GUID())
		{
			return;
		}

			SceneLoader::Save(activeScene);
	}

	void SceneManager::AddScene(const std::string& aPath)
	{
		std::filesystem::path path = std::filesystem::relative(aPath, PathManager::GetAssetsPath());

		std::string name = path.filename().stem().string();
		myNameToIdx[name] = (unsigned)myScenePaths.size();
		myScenePaths.push_back(path.generic_string());
	}

	void SceneManager::LoadSceneData()
	{
		//	using namespace rapidjson;

		//	const std::vector<std::string>& sceneIndex = Settings::BuildSettings::GetSceneIndex();
		//	if (sceneIndex.empty()) return;

		//	for (int i = 0; i < sceneIndex.size(); i++)
		//	{
		//		myNameToIdx[std::filesystem::path(sceneIndex[i]).filename().stem().generic_string()] = i;
		//		myScenePaths.push_back(sceneIndex[i]);
		//	}
	}

	void SceneManager::SaveSceneData()
	{
		//Settings::BuildSettings::SetSceneIndex(myScenePaths);
		//Settings::BuildSettings::Save();
	}

	void SceneManager::ClearScene()
	{
		myActiveScene = "";

		CommandListManager::ResetAllCommandLists();

		ComponentManager::Clear();
		Reflection::ReflectionManager::ClearList();

		PhysicsEngine::CleanUp();
	}

	std::unordered_map<std::string, unsigned>& SceneManager::GetNameToIdx() { return myNameToIdx; }
	std::vector<std::string>& SceneManager::GetScenePaths() { return myScenePaths; }

	const char* SceneManager::GetActiveScene()
	{
		return myActiveScene.c_str();
	}

	const Assets::Scene& SceneManager::GetActiveSceneAsset()
	{
		return activeScene;
	}

	void SceneManager::SetActiveScene(const char* anActiveScene)
	{
		myActiveScene = anActiveScene;
		Settings::EditorSettings::SetLastActiveScene(myActiveScene);
	}

	SceneManager::SceneType SceneManager::GetActiveSceneType()
	{
		return myActiveSceneType;
	}

	void SceneManager::SetActiveSceneType(SceneType aType)
	{
		myActiveSceneType = aType;
	}
}
