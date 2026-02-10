#include "TextureData.h"

#include "OpenGL/GLFW/glfw3.h"

Eclipse::TextureData::~TextureData()
{
	glDeleteTextures(1, &textureID);
}
