#include "AssetEngine/Editor/Importer/TypeImporters/EditorTextureImporter.h"

#include "AssetEngine/Editor/MetaFile/AssetMetaManager.h"
#include "AssetEngine/Editor/MetaFile/MetaFileRegistry.h"
#include "AssetEngine/Editor/GUID/GuidGenerator.h"

#include "AssetEngine/Editor/Importer/ImportSettings/AssetImportSettings.h"

#include <fstream>
#include <cereal/archives/json.hpp>

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#endif // !STB_IMAGE_IMPLEMENTATION

#ifndef STB_IMAGE_RESIZE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image/stb_image_resize.h"
#endif // !STB_IMAGE_RESIZE_IMPLEMENTATION

#include "AssetEngine/Data/TextureData.h"
#include "AssetEngine/SupportedTypes.h"

namespace Eclipse
{
	void TextureImporter::Export(const AssetMetaSettings& metaSettings, std::ofstream& outStream, const std::filesystem::path& aPath)
	{
		unsigned char* pixelData;
		TextureData data;
		{
			stbi_set_flip_vertically_on_load(true);
			pixelData = stbi_load(aPath.generic_string().c_str(), &data.width, &data.height, &data.channels, 0);
		}

		int type = (int)AssetType::Texture;
		outStream.write(reinterpret_cast<const char*>(&type), sizeof(int));
		outStream.write(reinterpret_cast<const char*>(&data.width), sizeof(int));
		outStream.write(reinterpret_cast<const char*>(&data.height), sizeof(int));
		outStream.write(reinterpret_cast<const char*>(&data.channels), sizeof(int));
		outStream.write(reinterpret_cast<const char*>(pixelData), data.width * data.height * data.channels);

		stbi_image_free(pixelData);
	}
}