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

		AudioManager::CreateAudio(outResource);
	}
}