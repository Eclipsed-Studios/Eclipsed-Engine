#pragma once

#include "AssetEngine/Assets/Asset.h"

#include "AssetEngine/BinaryFormats/PrefabData.h"


namespace Eclipse::Assets
{
	struct Prefab : public Asset<PrefabData> {
		ASSET_IMPL(Prefab, PrefabData)

	public:
	};
}