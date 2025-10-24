#pragma once

#include "CookedAsset.h"
#include "AssetEngine/Models/ImportedAssets.h"
#include "AssetEngine/Models/AssetDatas/Binary/TextureBinaryData.h"

#include "TypeCookers/Texture/TextureCooker.h"

namespace Eclipse::Assets
{
	class AssetCooker
	{
	public:
		static CookedAsset Cook(const ImportedAsset& asset);

	private:
		static inline TextureCooker textureCooker{};
	};
}

#include "AssetCooker.inl"