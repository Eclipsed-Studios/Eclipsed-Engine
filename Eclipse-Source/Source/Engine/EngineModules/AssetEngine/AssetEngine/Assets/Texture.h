#pragma once

#include "Asset.h"

namespace Eclipse
{
	enum TextureWrapMode
	{
		Repeat = 0x2901,
		RepeatMirror = 0x8370,
		ClampToEdge = 0x812F,
		ClampToBorder = 0x812D
	};

	enum SamplingType
	{
		Point = 0x2600,
		Bilinear = 0x2601,
	};

	namespace Assets
	{
		struct TextureHandle;
		class TextureManager;
	}

	class Texture final
	{
		ASSET_OPERATORS_DEF(Texture, Assets::TextureHandle, Assets::TextureManager);

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