#include "AssetPipeline.h"

#include "AssetScanner.h"
#include "AssetImporter/AssetImporter.h"
#include "AssetCooker/AssetCooker.h"
#include "CookedAssetWriter.h"
#include "AssetRegistry.h"
#include "PathManager.h"

/*
void AssetPipeline::Run()
{
	metaManager.Load();
	for (auto& asset : scanner.FindNewAssets()) {
		auto imported = importer.Import(asset);
		auto cooked = cooker.Cook(imported);
		writer.Write(cooked);
		metaManager.Update(asset, cooked);
	}
	metaManager.Save();
}
*/

namespace Eclipse::Assets
{
	void AssetPipeline::Init()
	{
		if (!PathManager::ProjectSet()) return;

		AssetRegistry::GetInstance().Load();
		for (AssetScannerEntry& asset : AssetScanner::FindModifiedAssets())
		{
			std::string fullpath = asset.fullPath.generic_string();
			std::string relpath = asset.relPath.generic_string();

			ImportedAsset imported;
			AssetImporter::Import(fullpath.c_str(), relpath.c_str(), imported);

			if (!imported.succesful) continue;

			AssetRegistry::GetInstance().RegisterAsset(fullpath, relpath, imported.type);
			
			if (imported.needsCooking)
			{
				CookedAsset cooked = AssetCooker::Cook(imported);
				CookedAssetWriter::Write(cooked);
			}
		}

		AssetRegistry::GetInstance().Save();
	}
}