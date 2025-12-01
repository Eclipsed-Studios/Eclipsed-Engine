#include "CookedAssetWriter.h"

#include <fstream>
#include "AssetEngine/PathManager.h"

#include "CoreEngine/Files/File.h"

namespace Eclipse::Assets
{
	void CookedAssetWriter::Write(const CookedAsset& cookedAsset)
	{
		const std::filesystem::path path = (PathManager::GetCookedAssetsDir() / (std::to_string(cookedAsset.id) + ".asset"));
		const std::string pathString = path.generic_string();

		Utilities::File file(pathString.c_str(), std::ios::binary | std::ios::out);
		file.Write(cookedAsset.data.data(), cookedAsset.size);
	}
}