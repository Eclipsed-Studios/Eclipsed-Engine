#pragma once

#include "Asset.h"

namespace Eclipse
{
	namespace Assets
	{
		struct TextureHandle;
		class TextureManager;
	}

	class Textures final
	{
		ASSET_OPERATORS_DEF(Textures, Assets::TextureHandle, Assets::TextureManager);

	public:
		int GetWidth() const;
		int GetHeight() const;

		float GetAspectRatio() const;

		size_t GetAssetID() const;
		unsigned GetTextureID() const;

		const Math::Vector2f& GetTextureSizeNormilized() const;
		float GetDimDivOne() const;

		void Bind(int slot = 0) const;
		void Unbind(int slot = 0) const;
	};
}