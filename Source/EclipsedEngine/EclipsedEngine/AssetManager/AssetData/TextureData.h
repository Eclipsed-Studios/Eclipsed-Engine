#pragma once

#include "AssetData.h"
#include "EclipsedEngine/Core/Math/Vector/Vector2.h"
#include "EclipsedEngine/Core/Math/RectSizePos.h"

namespace Eclipse::Assets
{
	struct TextureData : public AssetData
	{
		int width = 0;
		int height = 0;
		int channels = 0;

		Math::Vector2f invDimensions;
		Math::Vector2f sizeNormalized;

		unsigned int textureID = 0;

		std::vector<Math::RectSizePos> spriteRects;

		virtual void Bind(unsigned slot = 0) = 0;
		virtual void Unbind(unsigned slot = 0) = 0;

	protected:
		unsigned boundSlot = 0;
	};
}