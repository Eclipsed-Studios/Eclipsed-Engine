#include "AssetEngine/Managers/MaterialManager.h"

#include "AssetEngine/AssetBinaryLoader/TypeLoaders/Material/MaterialLoader.h"
#include "AssetEngine/AssetRegistry.h"

namespace Eclipse::Assets
{
	Material MaterialManager::Get(const size_t& id)
	{
		if (idToAssetHandle.find(id) != idToAssetHandle.end()) return ConstructAsset(id);
		else return Load(id);
	}

	Material MaterialManager::GetDefault()
	{
		static size_t id = AssetRegistry::GetInstance().GetIdFromPath("EngineAssets/Default/Materials/Default_2D_Material.mat");
		return Get(id);
	}

	MaterialLoader& MaterialManager::GetLoader()
	{
		static Assets::MaterialLoader loader{};
		return loader;
	}


	void MaterialManager::Reload(const size_t& id)
	{
		Assets::MaterialHandle* handle = idToAssetHandle[id];

		int refcount = handle->refCount;
		GetLoader().Load(id, handle);

		handle->refCount = refcount;
	}

	Material MaterialManager::Load(const size_t& id)
	{
		idToAssetHandle[id] = GetLoader().Load(id);
		return ConstructAsset(id);
	}

	Material MaterialManager::ConstructAsset(const size_t& id)
	{
		Material asset(idToAssetHandle[id]);
		asset.Create();

		return asset;
	}
}