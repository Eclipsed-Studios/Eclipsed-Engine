#include "AssetEngine/Managers/MaterialManager.h"

#include "AssetEngine/AssetBinaryLoader/TypeLoaders/Material/MaterialLoader.h"

namespace Eclipse::Assets
{
	Materials MaterialManager::Get(const size_t& id)
	{
		if (idToAssetHandle.find(id) != idToAssetHandle.end()) return ConstructAsset(id);
		else return Load(id);
	}

	Materials MaterialManager::Load(const size_t& id)
	{
		static Assets::MaterialLoader loader{};

		idToAssetHandle[id] = loader.Load(id);
		return ConstructAsset(id);
	}

	Materials MaterialManager::ConstructAsset(const size_t& id)
	{
		Materials asset(idToAssetHandle[id]);

		return asset;
	}
}