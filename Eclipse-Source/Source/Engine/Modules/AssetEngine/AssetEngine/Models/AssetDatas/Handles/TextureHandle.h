#pragma once

#include "AssetHandle.h"
#include "CoreEngine/Math/RectSizePos.h"
#include <vector>

namespace Eclipse::Assets 
{
	struct TextureHandle : public AssetHandle
	{
		int width = 0, height = 0;
		int channels;

		unsigned textureID = 0;

		Math::Vector2f dimDivOne;
		Math::Vector2f sizeNormalized;

		std::vector<Math::RectSizePos> rects;
	};
};