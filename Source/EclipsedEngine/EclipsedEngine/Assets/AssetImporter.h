#pragma once

#include <string>
#include <filesystem>

#include "EclipsedEngine.Core.hpp"

namespace Eclipse::Assets
{
	struct AssetMeta;
	class ECL_API AssetImporter
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