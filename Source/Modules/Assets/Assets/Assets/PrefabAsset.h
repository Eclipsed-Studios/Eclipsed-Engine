#pragma once

#include "Assets/Assets/Asset.h"

#include "Assets/BinaryFormats/PrefabData.h"

#include "Assets.Core.hpp"

namespace Eclipse::Assets
{
	struct ASSET_API Prefab : public Asset<PrefabData> {
		ASSET_IMPL(Prefab, PrefabData)

	public:
	};
}