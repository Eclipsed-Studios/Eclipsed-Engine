#pragma once

#include "Math/Vector/Vector2.h"

#include "Abstract/AbstractResource.h"

namespace ENGINE_NAMESPACE
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

	class Texture : public AbstractResource
	{
		BASE_RESOURCE(Texture)

	public:
		friend class AssetLoader;
		friend class SpriteRendrer2D;

		void Bind();

		unsigned GetTextureID();

	private:
		int width, height;
		int channels;

		Math::Vector2f spriteDimDivOne;

		unsigned textureID = 0;
	};
}