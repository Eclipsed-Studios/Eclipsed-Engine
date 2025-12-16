#pragma once

#include "AssetEngine/AssetBinaryLoader/TypeLoaders/TypeLoader.h"
#include "AssetEngine/Models/AssetDatas/Handles/AudioClipHandle.h"


namespace Eclipse::Assets
{
	class AudioClipLoader : public TypeLoader<AudioClipHandle>
	{
	public:
		AudioClipHandle* Load(const size_t& id) override;
		void Load(const size_t& id, AudioClipHandle* handle) override;
	};
}