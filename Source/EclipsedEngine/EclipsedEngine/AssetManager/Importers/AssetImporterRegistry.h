#pragma once

#include "EclipsedEngine.Core.hpp"
#include "IAssetImporter.h"
#include "EclipsedEngine/AssetManager/AssetTypes.h"

namespace Eclipse::Assets
{
	class ECL_API AssetImporterRegistry final
	{
	public:
		static void Register(AssetType type, IAssetImporter* importerType);
		static IAssetImporter* Get(AssetType type);

	private:
		static std::unordered_map<AssetType, IAssetImporter*> assetImporters;
	};
}