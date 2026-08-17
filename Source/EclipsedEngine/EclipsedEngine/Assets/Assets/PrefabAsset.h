#pragma once

#include "EclipsedEngine/Assets/Asset.h"

#include "EclipsedEngine/Assets/BinaryFormats/PrefabData.h"

#include "EclipsedEngine.Core.hpp"

namespace Eclipse::Assets
{
	struct ECL_API Prefab : public Asset<PrefabData> {
		ASSET_IMPL(Prefab, PrefabData)

	public:
	};
}