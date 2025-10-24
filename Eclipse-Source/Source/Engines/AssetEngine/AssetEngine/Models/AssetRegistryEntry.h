#pragma once

#include <filesystem>

namespace Eclipse::Assets
{
	struct AssetRegistryEntry final
	{
		std::filesystem::path path;
		size_t lastModified;
		int type;
	};
}