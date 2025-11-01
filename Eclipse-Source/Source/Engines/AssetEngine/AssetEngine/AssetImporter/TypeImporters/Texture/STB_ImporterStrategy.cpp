#include "STB_ImporterStrategy.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#endif // !STB_IMAGE_IMPLEMENTATION

#ifndef STB_IMAGE_RESIZE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image/stb_image_resize.h"
#endif // !STB_IMAGE_RESIZE_IMPLEMENTATION

#include "AssetEngine/PathManager.h"

namespace Eclipse::Assets
{
	void STB_ImporterStrategy::ImportAsset(TextureBinaryData& outData, const char* fullPath)
	{
		unsigned char* pixels = stbi_load(fullPath, &outData.width, &outData.height, &outData.channels, 0);
		outData.pixels.assign(pixels, pixels + (outData.width * outData.height * outData.channels));
		stbi_image_free(pixels);
	}
}

