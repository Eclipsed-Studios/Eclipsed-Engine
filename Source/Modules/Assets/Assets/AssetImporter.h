#pragma once

#include "Assets.Core.hpp"

#include <string>
#include <filesystem>

namespace Eclipse::Assets
{
	struct ASSET_API AssetMeta;

	class ASSET_API AssetImporter
	{
	private:
		AssetImporter() = delete;
		~AssetImporter() = delete;

	public:
		static void ImportAssets(const std::filesystem::path& root, const std::string& key = "Assets");
		static void ImportFile(const AssetMeta& meta);
		static void ImportBundle();
	};
}