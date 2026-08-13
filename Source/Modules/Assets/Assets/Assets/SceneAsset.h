#pragma once

#include "Assets/Assets/Asset.h"
#include "Assets/BinaryFormats/SceneData.h"
#include "Assets.Core.hpp"

namespace Eclipse::Assets
{
	struct ASSET_API Scene : public Asset<SceneData> {
		ASSET_IMPL(Scene, SceneData)

	public:


	};
}