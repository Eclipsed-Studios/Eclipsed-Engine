#pragma once

#include "AssetEngine/Data/TextureData.h"
#include "BaseAsset.h"

#include "CoreEngine/Math/RectSizePos.h"

namespace Eclipse
{
	class Texture
	{
	public:
		BASE_ASSET(Texture);

	public:
		int GetWidth() const;
		int GetHeight() const;

		float GetAspectRatio() const;

		unsigned GetTextureID() const;

		const Math::Vector2f& GetTextureSizeNormilized() const;
		Math::Vector2f GetDimDivOne() const;

		void Bind(int slot = 0) const;
		void Unbind(int slot = 0) const;

		// Temporary
		std::vector<Math::RectSizePos> GetRects() const;
	};
}