#include "CookedAssetWriter.h"

#include <fstream>
#include "AssetEngine/PathManager.h"

namespace Eclipse::Assets
{
	void CookedAssetWriter::Write(const CookedAsset& cookedAsset)
	{
		std::string path = (PathManager::GetCookedAssetsDir() / (std::to_string(cookedAsset.id) + ".asset")).generic_string();
		std::ofstream out(path);
		out.write(cookedAsset.data, cookedAsset.size);
		out.close();
	}
}