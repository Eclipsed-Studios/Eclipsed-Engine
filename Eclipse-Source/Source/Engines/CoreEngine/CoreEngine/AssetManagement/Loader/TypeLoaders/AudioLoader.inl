#include <../CoreEngine/CoreEngine/AssetManagement/Loader/AssetLoader.hpp>

#include <../CoreEngine/CoreEngine/AssetManagement/Resources/AudioClip.h>
#include "../CoreEngine/CoreEngine/Audio/AudioManager.h"

namespace Eclipse
{
	template <>
	inline void AssetLoader::LoadFromPath(const char* aPath, AudioClip& outResource)
	{
		
		std::filesystem::path resolvedPath = aPath;
		if (resolvedPath.is_relative())
		{
			resolvedPath = std::filesystem::current_path().parent_path().generic_string() + "/" + resolvedPath.string();
		}
		else if (resolvedPath.is_absolute())
		{
			resolvedPath = aPath;
		}
		outResource = AudioClip(resolvedPath.string().c_str());

#ifdef _GAME
		size_t id = std::hash<std::string>{}(std::filesystem::path(aPath).generic_string());
		std::ifstream in(SOURCE_PATH "Bin/assets.bundle", std::ios::binary);

		if (AssetLoader::loadedDatas.find(id) != AssetLoader::loadedDatas.end())
		{
			in.seekg(AssetLoader::loadedDatas[id].offset, std::ios::beg);

			std::vector<unsigned char> rawData;
			rawData.resize(AssetLoader::loadedDatas[id].size);

			in.read(reinterpret_cast<char*>(rawData.data()), AssetLoader::loadedDatas[id].size);
			in.close();

		AudioManager::CreateAudioFromMemory((const char*)rawData.data(), AssetLoader::loadedDatas[id].size, outResource);
		}
#else
		AudioManager::CreateAudioFromPath(outResource);
#endif
	}
}