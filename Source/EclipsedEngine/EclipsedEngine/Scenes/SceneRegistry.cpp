#include "SceneRegistry.h"

#include <stdexcept>

#include "Assets/Core/AssetDatabase.h"
#include "Core/MainSingleton.h"

namespace Eclipse
{
	SceneRegistry::SceneRegistry()
	{
		if (!MainSingleton::Exists<Assets::AssetDatabase>())
			return;

		Assets::AssetDatabase& database = MainSingleton::GetInstance<Assets::AssetDatabase>();
		const std::vector<Assets::GUID>& guids = database.GetGUIDsFromAssetType(Assets::AssetType::Scene);
		if (guids.empty()) 
			return;

		for (const Assets::GUID& guid : guids)
		{
			const Assets::AssetMeta& meta = database.GetProcessedFile(guid);
			registeredScenes.push_back({ meta.fileName, guid});
		}
	}

	const SceneEntry& SceneRegistry::GetScene(Assets::GUID guid)
	{
		for (const SceneEntry& entry : registeredScenes)
		{
			if (entry.guid == guid) return entry;
		}

		throw std::runtime_error("The scene is not registered. GUID dont exist.");
	}

	const SceneEntry& SceneRegistry::GetScene(const std::string& name)
	{
		for (const SceneEntry& entry : registeredScenes)
		{
			if (entry.name == name) return entry;
		}

		throw std::runtime_error("The scene is not registered. NAME dont exist.");
	}
}