#pragma once

#include "AssetData.h"
#include "CoreEngine/Math/Vector/Vector2.h"

namespace Eclipse
{
	struct TextureData : public AssetData {
		int width = 0;
		int height = 0;
		int channels = 0;

		Math::Vector2f dimDivOne;
		Math::Vector2f sizeNormalized;

		unsigned int textureID = 0;
	};
}