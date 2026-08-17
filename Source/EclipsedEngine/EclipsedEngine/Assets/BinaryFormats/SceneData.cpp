#include "EclipsedEngine/Assets/BinaryFormats/TextureData.h"

#include "OpenGL/glad/glad.h"

namespace Eclipse::Assets
{
	TextureData::~TextureData()
	{
		if (textureID == 0) return;

		glDeleteTextures(1, &textureID);
	}
}