#include "AssetEngine/Managers/MaterialManager.h"

#include "AssetEngine/AssetBinaryLoader/TypeLoaders/Material/MaterialLoader.h"
#include "AssetEngine/AssetRegistry.h"

namespace Eclipse::Assets
{
	Materials MaterialManager::Get(const size_t& id)
	{
		if (idToAssetHandle.find(id) != idToAssetHandle.end()) return ConstructAsset(id);
		else return Load(id);
	}

	Materials MaterialManager::GetDefault()
	{
		static size_t id = AssetRegistry::GetInstance().GetIdFromPath("EngineAssets/Default/Materials/Default_2D_Material.mat");
		return Get(id);
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
		asset.Create();

		return asset;
	}
}