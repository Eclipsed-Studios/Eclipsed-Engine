#pragma once

#include "AssetEngine/Managers/AssetManager.h"

#include "AssetEngine/Assets/AudioClip.h"


namespace Eclipse::Assets
{
	class AudioClipLoader;
	class AudioClipManager final : public AssetManager<class AudioClip, class Assets::AudioClipHandle>
	{
	public:
		AudioClip Get(const size_t& id) override;

	protected:
		AudioClipLoader& GetLoader();

		void Reload(const size_t& id) override;

		AudioClip Load(const size_t& id) override;
		AudioClip ConstructAsset(const size_t& id) override;
	};
}