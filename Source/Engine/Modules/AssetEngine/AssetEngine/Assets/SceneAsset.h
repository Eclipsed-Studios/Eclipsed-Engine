#pragma once

#include "AssetEngine/Assets/Asset.h"
#include "AssetEngine/BinaryFormats/SceneData.h"

namespace Eclipse::Assets
{
	struct Scene : public Asset<SceneData> {
		ASSET_IMPL(Scene, SceneData)

	public:


	};
}