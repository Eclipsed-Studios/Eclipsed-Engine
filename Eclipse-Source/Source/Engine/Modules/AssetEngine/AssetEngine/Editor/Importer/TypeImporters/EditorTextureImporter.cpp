#include "AssetEngine/Editor/Importer/TypeImporters/EditorTextureImporter.h"

#include "AssetEngine/Editor/MetaFile/AssetMetaManager.h"
#include "AssetEngine/Editor/MetaFile/MetaFileRegistry.h"
#include "AssetEngine/Editor/GUID/GuidGenerator.h"

#include "AssetEngine/Editor/Importer/ImportSettings/AssetImportSettings.h"

#include <fstream>
#include <cereal/archives/json.hpp>
#include "AssetEngine/Helper/STB_Helper.h"
#include "AssetEngine/Data/TextureData.h"
#include "AssetEngine/SupportedTypes.h"

#include <rapidjson/filereadstream.h>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>

namespace Eclipse
{
	void TextureImporter::Export(const AssetMetaSettings& metaSettings, std::ofstream& outStream, const std::filesystem::path& aPath)
	{
		TextureData data;
		
		
		int type = (int)AssetType::Texture;
		outStream.write(reinterpret_cast<const char*>(&type), sizeof(int));
		outStream.write(reinterpret_cast<const char*>(&data.width), sizeof(int));
		outStream.write(reinterpret_cast<const char*>(&data.height), sizeof(int));
		outStream.write(reinterpret_cast<const char*>(&data.channels), sizeof(int));
		
		unsigned char* pixelData;
		pixelData = STB_Helper::Load_Texture_STB(aPath.generic_string().c_str(), data.width, data.height, data.channels, true);
		outStream.write(reinterpret_cast<const char*>(pixelData), data.width * data.height * data.channels);
		STB_Helper::FreeData_STB(pixelData);

		TextureAssetMetaSettings texMetaSettings = LoadOrCreateMeta<TextureAssetMetaSettings>(aPath);
		int dataAmount = texMetaSettings.spriteRects.size();
		outStream.write(reinterpret_cast<const char*>(&dataAmount), sizeof(int));
		outStream.write(reinterpret_cast<const char*>(texMetaSettings.spriteRects.data()), dataAmount);
	}
}