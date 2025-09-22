#pragma once

namespace Eclipse
{
	class SceneManager
	{
	public:
		static void LoadScene(const std::string& name);
		static void LoadScene(unsigned idx);

		static void SaveScenes();

		static void AddScene(const std::string& aPath);

		static void LoadSceneData();
		static void SaveSceneData();

		static std::unordered_map<std::string, unsigned>& GetNameToIdx();
		static std::vector<std::string>& GetScenePaths();
		static std::vector<Scene>& GetLoadedScenes();

	private:
		static inline std::vector<Scene> loadedScenes;

	private:
		static inline std::unordered_map<std::string, unsigned> nameToIdx;
		static inline std::vector<std::string> scenePaths;
	};
}