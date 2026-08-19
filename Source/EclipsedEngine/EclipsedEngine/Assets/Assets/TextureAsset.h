#pragma once

#include "EclipsedEngine/Assets/Asset.h"
#include "EclipsedEngine/Assets/BinaryFormats/TextureData.h"

#include "EclipsedEngine/Core/Math/Vector/Vector2.h"
#include "EclipsedEngine.Core.hpp"

namespace Eclipse::Assets
{
	struct ECL_API Texture : public Asset<TextureData> {
		ASSET_IMPL(Texture, TextureData)

	public:
		Math::Vector2f GetDimDivOne() const;
		Math::Vector2f GetSizeNormalized() const;

		int GetWidth() const;
		int GetHeight() const;
		int GetChannels() const;

		const std::vector<Math::RectSizePos> GetSpriteRects() const;

	public:
		float GetAspectRatio() const;

		unsigned GetTextureID() const;

		const Math::Vector2f& GetTextureSizeNormilized() const;
	};
}