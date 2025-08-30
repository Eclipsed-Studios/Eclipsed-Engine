#pragma once

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
		void Bind();

		unsigned GetTextureID();

	private:
		int width, height;
		int channels;

		unsigned textureID = 0;
	};
}