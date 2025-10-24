#include "AssetScanner.h"

#include "PathManager.h"
#include "AssetRegistry.h"

namespace Eclipse::Assets
{
	std::vector<std::filesystem::path> AssetScanner::FindModifiedAssets()
	{
		namespace fs = std::filesystem;

		std::vector<std::filesystem::path> assetList;

		for (auto& entry : fs::recursive_directory_iterator(PathManager::GetAssetDir()))
		{
			if (fs::is_directory(entry)) continue;

			size_t lastModTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::filesystem::last_write_time(entry).time_since_epoch()).count();
			fs::path relPath = fs::relative(entry, PathManager::GetAssetDir());

			if (AssetRegistry::GetInstance().IsRegistered(relPath))
			{
				AssetRegistryEntry entry = AssetRegistry::GetInstance().GetRegisteredAsset(relPath);

				if (lastModTime > entry.lastModified)
				{
					assetList.push_back(relPath);
					continue;
				}
			}

			if (AssetRegistry::GetInstance().IsRegistered(relPath)) continue;
			assetList.push_back(relPath);
		}

		std::vector<size_t> assetsToRemove;
		for (auto& [id, data] : AssetRegistry::GetInstance().GetRegisteredAssets())
		{
			if (!fs::exists(PathManager::GetAssetDir() / data.path))
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

		return assetList;
	}

	std::vector<std::filesystem::path> AssetScanner::FindNewAssets()
	{
		namespace fs = std::filesystem;

		std::vector<std::filesystem::path> assetList;

		fs::path path = PathManager::GetAssetDir();
		for (auto& entry : fs::recursive_directory_iterator(PathManager::GetAssetDir()))
		{
			if (fs::is_directory(entry)) continue;

			fs::path relPath = fs::relative(entry, PathManager::GetAssetDir());
			if (AssetRegistry::GetInstance().IsRegistered(relPath)) continue;

			assetList.push_back(relPath);
		}

		return assetList;
	}

	std::vector<std::filesystem::path> AssetScanner::FindChangedAssets()
	{
		namespace fs = std::filesystem;

		std::vector<std::filesystem::path> assetList;

		fs::path path = PathManager::GetAssetDir();
		for (auto& entry : fs::recursive_directory_iterator(PathManager::GetAssetDir()))
		{
			if (fs::is_directory(entry)) continue;

			size_t lastModTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::filesystem::last_write_time(PathManager::GetAssetDir() / path).time_since_epoch()).count();
			fs::path relPath = fs::relative(entry, PathManager::GetAssetDir());
			AssetRegistryEntry entry = AssetRegistry::GetInstance().GetRegisteredAsset(relPath);

			if (lastModTime < entry.lastModified) continue;

			assetList.push_back(relPath);
		}

		return assetList;
	}
}