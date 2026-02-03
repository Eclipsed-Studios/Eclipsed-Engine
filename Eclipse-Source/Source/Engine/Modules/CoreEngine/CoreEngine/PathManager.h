#pragma once

#include <filesystem>

namespace Eclipse
{
	class PathManager
	{
	public:
		static void Init(const std::string& projectPath);

		static bool ProjectSet();

	public:
		// THe path to all the game assets.
		static std::filesystem::path GetProjectRoot() { return projectRoot / "Project"; }

		// The path to the root and the cmake binary
		static std::filesystem::path GetProjectSourceRoot() { return projectRoot; }
		static std::filesystem::path GetAssetDir() { return GetProjectRoot() / assetDir; }
		static std::filesystem::path GetArtifactDir()  {return GetProjectRoot() / artifactDir; }
		static std::filesystem::path GetConfigDir() { return GetProjectRoot() / settingsDir; }

		static std::filesystem::path GetRelAssetDir() { return assetDir; }
		static std::filesystem::path GetRelCacheDir() { return artifactDir; }
		static std::filesystem::path GetRelConfigDir() { return settingsDir; }
		static std::filesystem::path GetEngineRoot() { return engineSourceRoot; }
		static std::filesystem::path GetEngineAssets() { return engineSourceRoot / "EngineAssets"; }		
		static std::filesystem::path GetEngineLocal() { return engineSourceRoot / "Local"; }

		// Helpers
		static std::filesystem::path GetRawAssetPath(const std::filesystem::path& assetPath);

	private:
		static inline std::filesystem::path engineSourceRoot;

		static inline std::filesystem::path projectRoot;

		static inline std::filesystem::path assetDir = "Assets";
		static inline std::filesystem::path artifactDir = "Artifacts";
		static inline std::filesystem::path settingsDir = "Settings";
	};
}