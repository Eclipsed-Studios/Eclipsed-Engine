#include "AssetImporterRegistry.h"

namespace Eclipse::Assets
{
	std::unordered_map<AssetType, IAssetImporter*> AssetImporterRegistry::assetImporters = { };

	void AssetImporterRegistry::Register(AssetType type, IAssetImporter* importerType)
	{
		assetImporters[type] = importerType;
	}

	IAssetImporter* AssetImporterRegistry::Get(AssetType type)
	{
		if (assetImporters.find(type) != assetImporters.end())
			return assetImporters[type];

		return nullptr;
	}
}