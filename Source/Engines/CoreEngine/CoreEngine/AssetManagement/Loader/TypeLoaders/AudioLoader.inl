#include <AssetManagement/Loader/AssetLoader.hpp>

#include <AssetManagement/Resources/AudioClip.h>
#include "AssetManagement/Loader/ResourceLoaderHelper.h"

#include <glad/glad.h>

#include "Audio/AudioManager.h"

namespace ENGINE_NAMESPACE
{
	template <>
	inline void AssetLoader::LoadFromPath(const char* aPath, AudioClip& outResource)
	{
		outResource = AudioClip(aPath);

		AudioManager::CreateAudio(outResource);
	}
}