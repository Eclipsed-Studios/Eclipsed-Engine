#include "AssetLoader.hpp"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#endif // !STB_IMAGE_IMPLEMENTATION

unsigned char* ENGINE_NAMESPACE::AssetLoader::Load_Texture_STB(const char* aPath, Texture& outResource)
{
	stbi_set_flip_vertically_on_load(true);
	return stbi_load(aPath, &outResource.width, &outResource.height, &outResource.channels, 0);
}

void ENGINE_NAMESPACE::AssetLoader::FreeData_STB(unsigned char* someData)
{
	stbi_image_free(someData);
}
