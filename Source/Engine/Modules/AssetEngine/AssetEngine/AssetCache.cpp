#include "AssetCache.h"

#include <stdexcept>

namespace Eclipse::Assets
{
	AssetData* AssetCache::Get(GUID guid)
	{
		auto it = loadedAssets.find(guid);
		if (it != loadedAssets.end()) return loadedAssets[guid];

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
		if (it != loadedAssets.end()) delete loadedAssets[guid];
	}
}