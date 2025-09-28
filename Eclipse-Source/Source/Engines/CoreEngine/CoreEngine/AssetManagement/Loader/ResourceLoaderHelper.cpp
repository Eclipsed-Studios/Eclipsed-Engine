#include "ResourceLoaderHelper.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#endif // !STB_IMAGE_IMPLEMENTATION

#ifndef STB_IMAGE_RESIZE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image/stb_image_resize.h"
#endif // !STB_IMAGE_RESIZE_IMPLEMENTATION

#include "AssetManagement/Resources/Texture.h"

namespace Eclipse
{
	unsigned char* ResourceLoaderHelper::Load_Texture_STB(const char* aPath, Texture& outResource, bool flipVertically)
	{
		stbi_set_flip_vertically_on_load(flipVertically);
		return stbi_load(aPath, &outResource.width, &outResource.height, &outResource.channels, 0);
	}

	unsigned char* ResourceLoaderHelper::Load_Texture_STB(const char* aPath, int& width, int& height, int& channels, bool flipVertically)
	{
		stbi_set_flip_vertically_on_load(flipVertically);
		return stbi_load(aPath, &width, &height, &channels, 0);
	}

	unsigned char* ResourceLoaderHelper::Resize_STB(unsigned char* original, int originalWidth, int originalHeight, int newWidth, int newHeight, int channels)
	{
		unsigned char* resized = new unsigned char[newWidth * newHeight * channels];
		int ok = stbir_resize_uint8(original, originalWidth, originalHeight, 0,
			resized, newWidth, newHeight, 0,
			channels);



		stbi_image_free(original);

		return resized;
	}

	unsigned char* ResourceLoaderHelper::Load_Texture_From_Memory_STB(std::vector<unsigned char>& data, Texture& outResource, bool flipVertically)
	{
		stbi_set_flip_vertically_on_load(flipVertically);
		return stbi_load_from_memory(data.data(), (int)data.size(), &outResource.width, &outResource.height, &outResource.channels, 0);
	}

	void ResourceLoaderHelper::FreeData_STB(unsigned char* someData)
	{
		stbi_image_free(someData);
	}
}