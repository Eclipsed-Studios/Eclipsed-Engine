#include "AssetScanner.h"

#include "PathManager.h"
#include "AssetRegistry.h"

namespace Eclipse::Assets
{
	std::vector<AssetScannerEntry> AssetScanner::FindModifiedAssets()
	{
		namespace fs = std::filesystem;

		std::vector<AssetScannerEntry> assetList;
		{ // Project assets
			for (auto& entry : fs::recursive_directory_iterator(PathManager::GetAssetDir()))
			{
				if (fs::is_directory(entry)) continue;

				size_t lastModTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::filesystem::last_write_time(entry).time_since_epoch()).count();
				fs::path relPath = fs::relative(entry, PathManager::GetAssetDir());

				if (AssetRegistry::GetInstance().IsRegistered(relPath))
				{
					AssetRegistryEntry regEntry = AssetRegistry::GetInstance().GetRegisteredAsset(relPath);

					if (lastModTime > regEntry.lastModified)
					{
						assetList.push_back({ entry.path(), relPath });
						continue;
					}
				}

				if (AssetRegistry::GetInstance().IsRegistered(relPath)) continue;
				assetList.push_back({ entry.path(), relPath });
			}

			std::vector<size_t> assetsToRemove;
			for (auto& [id, data] : AssetRegistry::GetInstance().GetRegisteredAssets())
			{
				if (!fs::exists(data.path))
				{
					fs::path fullPath = PathManager::GetCookedAssetsDir() / (std::to_string(id) + ".asset");
					fs::remove(fullPath);

					assetsToRemove.push_back(id);
				}
			}

			for (auto& id : assetsToRemove)
			{
				AssetRegistry::GetInstance().UnregisterAsset(id);
			}
		}


		{ // Engine assets
			for (auto& entry : fs::recursive_directory_iterator(PathManager::GetEngineAssets()))
			{
				if (fs::is_directory(entry)) continue;

				size_t lastModTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::filesystem::last_write_time(entry).time_since_epoch()).count();
				fs::path relPath = fs::relative(entry, PathManager::GetEngineRoot());

				if (AssetRegistry::GetInstance().IsRegistered(relPath))
				{
					AssetRegistryEntry regEntry = AssetRegistry::GetInstance().GetRegisteredAsset(relPath);

					if (lastModTime > regEntry.lastModified)
					{
						assetList.push_back({ entry.path(), relPath });
						continue;
					}
				}

				if (AssetRegistry::GetInstance().IsRegistered(relPath)) continue;
				assetList.push_back({ entry.path(), relPath });
			}

			std::vector<size_t> assetsToRemove;
			for (auto& [id, data] : AssetRegistry::GetInstance().GetRegisteredAssets())
			{
				if (!fs::exists(data.path))
				{
					fs::path fullPath = PathManager::GetCookedAssetsDir() / (std::to_string(id) + ".asset");
					fs::remove(fullPath);

					assetsToRemove.push_back(id);
				}
			}

			for (auto& id : assetsToRemove)
			{
				AssetRegistry::GetInstance().UnregisterAsset(id);
			}
		}

		return assetList;
	}
}