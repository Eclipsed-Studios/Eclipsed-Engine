#pragma once

#include "EclipsedEngine/Assets/Asset.h"
#include "EclipsedEngine/Assets/BinaryFormats/SceneData.h"
#include "EclipsedEngine.Core.hpp"

namespace Eclipse::Assets
{
	struct ECL_API Scene : public Asset<SceneData> {
		ASSET_IMPL(Scene, SceneData)

	public:


	};
}