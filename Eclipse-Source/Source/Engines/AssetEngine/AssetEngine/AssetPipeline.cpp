#include "AssetPipeline.h"

#include "AssetScanner.h"
#include "AssetImporter/AssetImporter.h"
#include "AssetCooker/AssetCooker.h"
#include "CookedAssetWriter.h"
#include "AssetRegistry.h"

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
		AssetRegistry::GetInstance().Load();
		for (std::filesystem::path& asset : AssetScanner::FindModifiedAssets())
		{
			std::string pathString = asset.generic_string();

			ImportedAsset imported;
			AssetImporter::Import(pathString.c_str(), imported);

			if (!imported.succesful) continue;
			
			CookedAsset cooked = AssetCooker::Cook(imported);
			CookedAssetWriter::Write(cooked);
		}

		AssetRegistry::GetInstance().Save();
	}
}