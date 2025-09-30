#include "AssetLoader.hpp"

#include "rapidjson/rapidjson/document.h"
#include "rapidjson/rapidjson/filereadstream.h"

namespace Eclipse
{
	void AssetLoader::Init()
	{
		std::ifstream in(SOURCE_PATH "Bin/assets.bundle", std::ios::binary);

		int fileCount = 0;
		in.read(reinterpret_cast<char*>(&fileCount), sizeof(int));

		for (int i = 0; i < fileCount; ++i)
		{
			FileEntryData data;
			in.read(reinterpret_cast<char*>(&data), sizeof(FileEntryData));

			loadedDatas[data.id] = data;
		}
	}

}
