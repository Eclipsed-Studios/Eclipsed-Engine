#pragma once

#include <vector>
#include <filesystem>

namespace Eclipse::Assets
{
	struct AssetScannerEntry
	{
		std::filesystem::path fullPath;
		std::filesystem::path relPath;
	};

	class AssetScanner final
	{
	public:
		static std::vector<AssetScannerEntry> FindModifiedAssets();
	};
}