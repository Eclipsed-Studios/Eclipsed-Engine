#include "PrefabManager.h"

#include "AssetEngine/AssetRegistry.h"

namespace Eclipse::Assets
{
	Prefab PrefabManager::Get(const size_t& id)
	{
		if (idToAssetHandle.find(id) != idToAssetHandle.end()) return ConstructAsset(id);
		else return Load(id);
	}

	Prefab PrefabManager::Load(const size_t& id)
	{
		idToAssetHandle[id] = GetLoader().Load(id);
		return ConstructAsset(id);
	}

	PrefabLoader& PrefabManager::GetLoader()
	{
		static Assets::PrefabLoader loader{};
		return loader;
	}

	void PrefabManager::Reload(const size_t& id)
	{
	}

	Prefab PrefabManager::ConstructAsset(const size_t& id)
	{
		Prefab prefab(idToAssetHandle[id]);

		return prefab;
	}
}