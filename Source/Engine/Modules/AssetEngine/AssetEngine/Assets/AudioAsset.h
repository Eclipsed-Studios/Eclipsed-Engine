#pragma once

#include "AssetEngine/Assets/Asset.h"

#include "AssetEngine/BinaryFormats/AudioData.h"

namespace Eclipse::Assets
{
	struct AudioClip : public Asset<AudioData> {
		ASSET_IMPL(AudioClip, AudioData)

	public:
	};
}