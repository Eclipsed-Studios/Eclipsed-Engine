#pragma once

#include "FileInfo.h"

namespace Eclipse
{
	struct FileEntry
	{
		std::vector<unsigned char> data;
		FileInfo info;
		size_t offset;
	};

#pragma pack(push, 1)
	struct FileEntryData
	{
		size_t id;
		size_t offset;
		size_t size;
	};
#pragma pack(pop)

	class AssetExporter
	{
	public:
		static void ExportAll();
	};
}