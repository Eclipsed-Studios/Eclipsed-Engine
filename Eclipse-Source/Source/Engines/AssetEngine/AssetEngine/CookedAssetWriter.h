#pragma once

#include "AssetEngine/AssetCooker/CookedAsset.h"

namespace Eclipse::Assets
{
	class CookedAssetWriter final
	{
	public:
		static void Write(const CookedAsset& cookedAsset);
	};
}