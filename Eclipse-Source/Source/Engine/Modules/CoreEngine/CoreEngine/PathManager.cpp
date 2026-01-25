#include "pch.h"

#include "PathManager.h"

#include "CoreEngine/Files/FileUtilities.h"

namespace Eclipse
{
	void PathManager::Init(const std::string& projectPath)
	{
		namespace fs = std::filesystem;

		engineSourceRoot = fs::current_path();
		std::cout << engineSourceRoot.string() << std::endl;

		projectRoot = fs::absolute(projectPath);
	}




	bool PathManager::ProjectSet()
	{
		return !projectRoot.empty();
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