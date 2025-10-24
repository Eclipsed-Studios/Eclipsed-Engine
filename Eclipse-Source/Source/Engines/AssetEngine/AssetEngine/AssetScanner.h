#pragma once

#include <vector>
#include <filesystem>

namespace Eclipse::Assets
{
	class AssetScanner final
	{
	public:
		static std::vector<std::filesystem::path> FindModifiedAssets();
		static std::vector<std::filesystem::path> FindNewAssets();
		static std::vector<std::filesystem::path> FindChangedAssets();
	};
}