#include <AssetManagement/Loader/AssetLoader.hpp>

#include <AssetManagement/Resources/AudioClip.h>
#include "AssetManagement/Loader/ResourceLoaderHelper.h"

#include <glad/glad.h>

#include "Audio/AudioManager.h"

namespace Eclipse
{
	template <>
	inline void AssetLoader::LoadFromPath(const char* aPath, AudioClip& outResource)
	{
		std::string folder = std::filesystem::current_path().parent_path().string();
		outResource = AudioClip((folder  + std::string(aPath)).c_str());

		AudioManager::CreateAudio(outResource);
	}
}