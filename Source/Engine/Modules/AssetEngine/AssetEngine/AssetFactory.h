#pragma once

#include "BinaryFormats/AssetData.h"

namespace Eclipse::Assets
{
	class AssetFactory
	{
	public:
		template <typename T>
		static T ConstructAsset(AssetData* assetData);
	};

	template<typename T>
	inline T AssetFactory::ConstructAsset(AssetData* assetData)
	{
		return T(assetData);
	}
}