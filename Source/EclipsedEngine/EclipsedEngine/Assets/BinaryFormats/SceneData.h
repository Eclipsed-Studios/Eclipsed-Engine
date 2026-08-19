#pragma once

#include "AssetData.h"
#include "EclipsedEngine/Core/Math/Vector/Vector2.h"
#include "EclipsedEngine/Core/Math/RectSizePos.h"

namespace Eclipse::Assets
{
	struct SceneData : public AssetData {
		~SceneData();

		std::string sourceBlob;
	};
}