#include "TextureCooker.h"

#include <filesystem>
#include "AssetEngine/AssetImporter/TypeImporters/Texture/STB_ImporterStrategy.h"

#include "AssetEngine/AssetCooker/CookedAsset.h"

namespace Eclipse::Assets
{
	void TextureCooker::Cook(const TextureBinaryData& data, CookedAsset& outData)
	{
		size_t headerSize = sizeof(int) // Width
			+ sizeof(int)				// Height
			+ sizeof(int)				// Channels
			+ sizeof(size_t);			// ID

		size_t pixelSize = data.width * data.height * data.channels;

		size_t totalSize = headerSize + pixelSize;

		outData.data.resize(totalSize);
		outData.size = totalSize;
		outData.id = data.id;

		char* ptr = outData.data.data();

		size_t totalWritten = 0;
		memcpy(ptr + totalWritten, &data.id, sizeof(size_t)); totalWritten += sizeof(size_t);
		memcpy(ptr + totalWritten, &data.width, sizeof(int)); totalWritten += sizeof(int);
		memcpy(ptr + totalWritten, &data.height, sizeof(int)); totalWritten += sizeof(int);
		memcpy(ptr + totalWritten, &data.channels, sizeof(int)); totalWritten += sizeof(int);

		memcpy(ptr + totalWritten, data.pixels.data(), pixelSize);
	}
}