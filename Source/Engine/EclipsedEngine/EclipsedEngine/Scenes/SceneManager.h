#pragma once

#include <vector>
#include <string>
#include <unordered_map>

#include "CoreEngine/Macros/defines.h"

#include "SceneRegistry.h"

#include "AssetEngine/Assets/SceneAsset.h"

namespace Eclipse
{
	class ECLIPSED_API SceneManager
	{
	public:
		static void Initialize();

		static void LoadScene(const std::string& name);
		static void LoadScene(const Assets::Scene& scene);
		static void LoadScene(Assets::GUID guid);

		static void UnloadScene();











		static void ReloadActiveScene();

		static void SaveScenes();
		static void SaveActiveScene();

		static void AddScene(const std::string& aPath);

		static void LoadSceneData();
		static void SaveSceneData();

		static void ClearScene();

		static std::unordered_map<std::string, unsigned>& GetNameToIdx();
		static std::vector<std::string>& GetScenePaths();
		static const char* GetActiveScene();

		
		enum SceneType
		{
			Default,
			Prefab
		};

		static void SetActiveSceneType(SceneType aType);
		static SceneType GetActiveSceneType();
		static void SetActiveScene(const char* anActiveScene);
		static inline unsigned ActivePrefabEditSceneID;
		
	private:
		static inline SceneType myActiveSceneType = Default;
		
		static inline std::string myActiveScene;

	private:
		static inline std::unordered_map<std::string, unsigned> myNameToIdx;
		static inline std::vector<std::string> myScenePaths;


		static SceneRegistry registry;







		static inline Assets::Scene activeScene;
	};
}