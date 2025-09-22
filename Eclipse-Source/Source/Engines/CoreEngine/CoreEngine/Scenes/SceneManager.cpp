#include "SceneManager.h"

#include "rapidjson/rapidjson/document.h"
#include "rapidjson/rapidjson/prettywriter.h"

#include "SceneLoader.h"

namespace Eclipse
{
	void SceneManager::LoadScene(const std::string& name)
	{
		SceneLoader::Load((SOURCE_PATH + scenePaths[nameToIdx[name]]).c_str());
	}

	void SceneManager::LoadScene(unsigned idx)
	{
		SceneLoader::Load((SOURCE_PATH + scenePaths[idx]).c_str());
	}

	void SceneManager::SaveScenes()
	{
	}

	void SceneManager::AddScene(const std::string& aPath)
	{
		std::filesystem::path path = SOURCE_PATH + aPath;

		std::string name = path.filename().stem().string();
		nameToIdx[name] = (unsigned)scenePaths.size();
		scenePaths.push_back(aPath);
	}

	void SceneManager::LoadSceneData()
	{
		using namespace rapidjson;

		std::ifstream in(ENGINE_SETTINGS_PATH);

		std::string jsonString((std::istreambuf_iterator<char>(in)),
			std::istreambuf_iterator<char>());

		in.close();

		Document d;
		if (!jsonString.empty())
		{
			d.Parse(jsonString.c_str());
		}

		Document::AllocatorType& alloc = d.GetAllocator();

		if (d.HasMember("scenes"))
		{
			Value& val = d["scenes"].GetArray();

			for (SizeType i = 0; i < val.Size(); i++)
			{
				const Value& sceneObj = val[i];

				std::string name = sceneObj["name"].GetString();
				std::string relativePath = sceneObj["relativePath"].GetString();
				int idx = sceneObj["idx"].GetInt();

				nameToIdx[name] = idx;

				if (scenePaths.empty()) scenePaths.push_back(relativePath);
				else scenePaths.insert(scenePaths.begin() + idx, relativePath);
			}
		}
	}

	void SceneManager::SaveSceneData()
	{
		using namespace rapidjson;

		std::ifstream in(ENGINE_SETTINGS_PATH);

		std::string jsonString((std::istreambuf_iterator<char>(in)),
			std::istreambuf_iterator<char>());

		in.close();

		Document d;
		if (!jsonString.empty())
		{
			d.Parse(jsonString.c_str());
		}

		Document::AllocatorType& alloc = d.GetAllocator();

		if (!d.HasMember("scenes"))
		{
			d.AddMember("scenes", Value(kArrayType), alloc);
		}

		Value& val = d["scenes"].GetArray();
		val.Clear();

		for (auto& [name, idx] : nameToIdx)
		{
			Value sceneData(kObjectType);
			sceneData.AddMember("name", Value(name.c_str(), alloc).Move(), alloc);
			sceneData.AddMember("relativePath", Value(scenePaths[idx].c_str(), alloc).Move(), alloc);
			sceneData.AddMember("idx", idx, alloc);

			val.PushBack(sceneData, alloc);
		}

		StringBuffer buffer;
		PrettyWriter<StringBuffer> writer(buffer);
		d.Accept(writer);

		std::ofstream ofs(ENGINE_SETTINGS_PATH);
		ofs << buffer.GetString();
		ofs.close();
	}

	std::unordered_map<std::string, unsigned>& SceneManager::GetNameToIdx() { return nameToIdx; }
	std::vector<std::string>& SceneManager::GetScenePaths() { return scenePaths; }
	std::vector<Scene>& SceneManager::GetLoadedScenes() { return loadedScenes; }
}