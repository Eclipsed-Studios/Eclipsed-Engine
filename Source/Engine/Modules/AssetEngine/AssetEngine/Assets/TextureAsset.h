#pragma once

#include "AssetEngine/Assets/Asset.h"
#include "AssetEngine/BinaryFormats/TextureData.h"

#include "CoreEngine/Math/Vector/Vector2.h"

namespace Eclipse::Assets
{
	struct Texture : public Asset<TextureData> {
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