#pragma once

#include <filesystem>

namespace Eclipse
{
	class PathManager
	{
	public:
		static void Init(const std::filesystem::path& projectRootPath);

	public:
		// Core directories
		static std::filesystem::path GetProjectRoot() { return projectRoot / projectRoot; }
		static std::filesystem::path GetAssetDir() { return projectRoot / assetDir; }
		static std::filesystem::path GetCacheDir()  {return projectRoot / cacheDir; }
		static std::filesystem::path GetCookedAssetsDir()  {return projectRoot / cookedAssetsDir; }
		static std::filesystem::path GetConfigDir() { return projectRoot / settingsDir; }

		static std::filesystem::path GetRelAssetDir() { return assetDir; }
		static std::filesystem::path GetRelCacheDir() { return cacheDir; }
		static std::filesystem::path GetRelCookedAssetsDir() { return cacheDir / cookedAssetsDir; }
		static std::filesystem::path GetRelConfigDir() { return settingsDir; }

		// Helpers
		static std::filesystem::path GetRawAssetPath(const std::filesystem::path& assetPath);
		static std::filesystem::path GetCookedAssetPath(const std::filesystem::path& assetPath);

	private:
		static inline std::filesystem::path engineSourceRoot;

		static inline std::filesystem::path projectRoot;

		static inline std::filesystem::path assetDir = "Assets";
		static inline std::filesystem::path cacheDir = "Cache";
		static inline std::filesystem::path cookedAssetsDir = cacheDir / "CookedAssets";
		static inline std::filesystem::path settingsDir = "Settings";
	};
}