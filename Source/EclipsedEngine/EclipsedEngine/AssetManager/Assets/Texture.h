#pragma once

#include "EclipsedEngine/AssetManager/Asset.h"
#include "EclipsedEngine/AssetManager/AssetData/TextureData.h"

namespace Eclipse::Assets
{
	struct Texture : public Asset
	{
	public:
		int GetWidth() const;
		int GetHeight() const;
		int GetChannels() const;

		Math::Vector2f GetInversedDimension() const;
		Math::Vector2f GetSizeNormalized() const;

		unsigned int GetTextureID() const;

		const std::vector<Math::RectSizePos>& GetSpriteRects() const;

		void Bind(unsigned slot = 0) const;
		void Unbind(unsigned slot = 0) const;

	private:
		TextureData* data;
	};
}