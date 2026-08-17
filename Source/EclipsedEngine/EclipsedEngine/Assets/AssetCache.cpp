#include "AssetCache.h"

#include <stdexcept>

#include "EclipsedEngine/Assets/IO/BinaryReader.h"
#include "AssetTypeRegistry.h"
#include "Metadata/AssetMeta.h"
#include "Core/AssetDatabase.h"
#include "BinaryFormats/AssetData.h"
#include "AssetTypes/IAssetType.h"
#include "Core/MainSingleton.h"

namespace Eclipse::Assets
{
	AssetData* AssetCache::Get(GUID guid)
	{
		auto it = loadedAssets.find(guid);
		if (it != loadedAssets.end() && loadedAssets[guid] != nullptr) return loadedAssets[guid];

		return nullptr;
	}
	
	AssetData* AssetCache::Store(GUID guid, AssetData* data)
	{
		auto it = loadedAssets.find(guid);
		if (it != loadedAssets.end()) throw std::runtime_error("The guid already exists");

		loadedAssets[guid] = data;
		return data;
	}

	void AssetCache::Delete(GUID guid)
	{
		auto it = loadedAssets.find(guid);
		if (it != loadedAssets.end())
		{
			delete loadedAssets[guid];
			loadedAssets.erase(guid);
		}
	}

	void AssetCache::MarkForReload(GUID guid)
	{
		pendingReload.push_back(guid);
	}

	void AssetCache::ProcessReloads()
	{
		for (const GUID& guid : pendingReload)
		{
			BinaryReader reader(guid);
			const AssetMeta& meta = MainSingleton::GetInstance<AssetDatabase>().GetProcessedFile(guid);
			IAssetType* type = AssetTypeRegistry::GetType(meta.type);
			type->Load(reader, meta, loadedAssets[guid]);
		}

		pendingReload.clear();
	}
}