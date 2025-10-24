#include "AssetImporter.h"

#include "AssetEngine/AssetCooker/AssetCooker.h"
#include "AssetEngine/AssetRegistry.h"
#include "AssetEngine/PathManager.h"

#include "rapidjson/rapidjson/document.h"
#include "rapidjson/rapidjson/prettywriter.h"
#include "rapidjson/rapidjson/reader.h"
#include "rapidjson/rapidjson/filereadstream.h"

#include <iomanip> 
#include <iterator>
#include <fstream>

#include "AssetEngine/SupportedTypes.h"

namespace Eclipse::Assets
{
	void AssetImporter::Import(const char* path, const char* rel, ImportedAsset& outAsset)
	{
		const std::string extension = std::filesystem::path(path).extension().generic_string();

		if (extensionToAssetType.find(extension) == extensionToAssetType.end())
			return; // The file is not supported.

		const AssetType type = extensionToAssetType.at(extension);

		outAsset.type = type;
		outAsset.succesful = true;

		AssetRegistry::GetInstance().RegisterAsset(path, rel, AssetType::Texture);


		switch (type)
		{
		case AssetType::Texture: textureImporter.Import(std::get<TextureBinaryData>(outAsset.data), path); break;
		}
	}
}