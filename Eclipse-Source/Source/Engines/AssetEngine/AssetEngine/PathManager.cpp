#include "PathManager.h"

namespace Eclipse
{
	void PathManager::Init(const std::filesystem::path& projectRootPath)
	{
		namespace fs = std::filesystem;

		engineSourceRoot = fs::current_path();

		projectRoot = fs::absolute(projectRootPath);
	}

	std::filesystem::path PathManager::GetRawAssetPath(const std::filesystem::path& assetPath)
	{
		return  GetAssetDir() / assetPath;
	}

	std::filesystem::path PathManager::GetCookedAssetPath(const std::filesystem::path& assetPath) 
	{
		return  GetCacheDir() / assetPath;
	}
}