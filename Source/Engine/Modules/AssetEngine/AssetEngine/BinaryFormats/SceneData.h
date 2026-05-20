#pragma once

#include "AssetData.h"
#include "CoreEngine/Math/Vector/Vector2.h"
#include "coreEngine/Math/RectSizePos.h"

namespace Eclipse::Assets
{
	struct SceneData : public AssetData {
		~SceneData();

		std::string sourceBlob;
	};
}