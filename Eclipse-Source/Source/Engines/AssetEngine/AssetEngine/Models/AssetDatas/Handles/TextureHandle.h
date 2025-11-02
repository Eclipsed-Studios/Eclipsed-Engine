#pragma once

#include "AssetHandle.h"
#include "Utilities/Math/RectSizePos.h"

namespace Eclipse::Assets 
{
	struct TextureHandle : public AssetHandle
	{
		int width = 0, height = 0;
		int channels;

		unsigned textureID = 0;

		float dimDivOne;
		Math::Vector2f sizeNormalized;

		std::vector<Math::RectSizePos> rects;
	};
};