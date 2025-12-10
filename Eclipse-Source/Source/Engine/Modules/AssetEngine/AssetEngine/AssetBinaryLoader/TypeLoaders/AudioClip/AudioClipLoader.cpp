#include "AudioClipLoader.h"
#include "AssetEngine/AssetRegistry.h"
#include "fmod/fmod.h"
#include "fmod/fmod.hpp"

#include "CoreEngine/MainSingleton.h"


namespace Eclipse::Assets
{	
	AudioClipHandle* AudioClipLoader::Load(const size_t& id)
	{
		AudioClipHandle* handle = new AudioClipHandle;

		Load(id, handle);
		return handle;
	}
	void AudioClipLoader::Load(const size_t& id, AudioClipHandle* handle)
	{
		auto& entry = AssetRegistry::GetInstance().GetRegisteredAsset(id);
		handle->assetID = id;

		FMOD_MODE mode = true ? FMOD_LOOP_NORMAL : FMOD_DEFAULT;

		FMOD::System* system = MainSingleton::GetInstance<FMOD::System*>();
		system->createSound(entry.path.generic_string().c_str(), mode, nullptr, &handle->sound);
	}
}
