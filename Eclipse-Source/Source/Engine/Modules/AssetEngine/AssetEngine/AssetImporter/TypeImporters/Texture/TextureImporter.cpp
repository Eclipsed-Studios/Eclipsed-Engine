#include "TextureImporter.h"

#include <filesystem>
#include "AssetEngine/AssetImporter/TypeImporters/Texture/STB_ImporterStrategy.h"
#include "AssetEngine/AssetRegistry.h"
#include "CoreEngine/PathManager.h"

namespace Eclipse::Assets
{
	TextureImporter::TextureImporter()
	{
		importers[Importer::STB] = new STB_ImporterStrategy();
	}

	void TextureImporter::Import(TextureBinaryData& outData, const char* path, const char* relPath)
	{
		const std::string extension = std::filesystem::path(path).extension().generic_string();

		if (typeToImporter.find(extension) == typeToImporter.end())
			return; // The file is not supported.

		outData.id = AssetRegistry::GetInstance().GetIdFromPath(relPath);

		std::filesystem::path fullPath = PathManager::GetAssetDir() / path;

		const Importer importer = typeToImporter.at(extension);
		importers[importer]->ImportAsset(outData, fullPath.string().c_str());
	}
}