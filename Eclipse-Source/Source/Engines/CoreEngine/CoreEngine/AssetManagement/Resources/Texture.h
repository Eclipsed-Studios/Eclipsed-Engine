#pragma once

#include "Math/Vector/Vector2.h"

#include "Abstract/AbstractResource.h"

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

	class Texture : public AbstractResource
	{
		BASE_RESOURCE(Texture)

	public:
		friend class SpriteRenderer2D;

		void Bind();

		unsigned GetTextureID();

		float GetTextureRatio() { return dimDivOne; }

		Math::Vector2i GetTextureSize() { return Math::Vector2i{ width, height }; }
		Math::Vector2i GetTextureSizeEngineUnits() { return Math::Vector2i{ static_cast<int>(static_cast<float>(width) * 0.01f), static_cast<int>(static_cast<float>(height) * 0.01f) }; }
		
		Math::Vector2f GetTextureSizeNormilized() { return Math::Vector2f{ 
			1.f, static_cast<float>(height) / width }; 
		}

	private:
		int width = 1, height = 1;
		int channels;

		Math::Vector2f spriteDimDivOne;
		float dimDivOne;

		unsigned textureID = 0;
	};
}