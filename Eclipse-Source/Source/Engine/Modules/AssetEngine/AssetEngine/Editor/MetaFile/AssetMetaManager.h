#pragma once

#include <unordered_set>
#include <string>
#include <filesystem>

namespace Eclipse
{
	using GUID = std::string;

	class AssetMetaManager
	{
	public:
		static std::filesystem::path CreateMetaFile(const std::filesystem::path& aPath);
		static std::filesystem::path GetMetaFile(const std::filesystem::path& aPath);
	};
}