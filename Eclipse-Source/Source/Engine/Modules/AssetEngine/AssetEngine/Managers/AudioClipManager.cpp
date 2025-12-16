#include "AssetEngine/Managers/AudioClipManager.h"

#include "AssetEngine/AssetBinaryLoader/TypeLoaders/AudioClip/AudioClipLoader.h"
#include "AssetEngine/AssetRegistry.h"

namespace Eclipse::Assets
{
	AudioClip AudioClipManager::Get(const size_t& id)
	{
		if (idToAssetHandle.find(id) != idToAssetHandle.end()) return ConstructAsset(id);
		else return Load(id);
	}

	AudioClipLoader& AudioClipManager::GetLoader()
	{
		static Assets::AudioClipLoader loader{};
		return loader;
	}

	void AudioClipManager::Reload(const size_t& id)
	{
	}

	AudioClip AudioClipManager::Load(const size_t& id)
	{
		idToAssetHandle[id] = GetLoader().Load(id);
		return ConstructAsset(id);
	}

	AudioClip AudioClipManager::ConstructAsset(const size_t& id)
	{
		AudioClip clip(idToAssetHandle[id]);

		return clip;
	}
}