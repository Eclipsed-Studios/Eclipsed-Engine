#pragma once

#include "EclipsedEngine/Assets/Asset.h"
#include "EclipsedEngine/Assets/BinaryFormats/TextureData.h"

#include "Core/Math/Vector/Vector2.h"

namespace Eclipse::Assets
{
	struct Texture : public Asset<TextureData> {
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

		void Bind(int slot = 0) const;
		void Unbind(int slot = 0) const;
	};
}