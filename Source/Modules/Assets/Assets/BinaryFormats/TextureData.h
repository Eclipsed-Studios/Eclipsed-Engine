#pragma once

#include "AssetData.h"
#include "Core/Math/Vector/Vector2.h"
#include "Core/Math/RectSizePos.h"

namespace Eclipse::Assets
{
	struct TextureData : public AssetData {
		~TextureData();

		int width = 0;
		int height = 0;
		int channels = 0;

		Math::Vector2f dimDivOne;
		Math::Vector2f sizeNormalized;

		unsigned int textureID = 0;

		std::vector<Math::RectSizePos> spriteRects;
	};
}