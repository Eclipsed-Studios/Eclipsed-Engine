#pragma once

#include "Assets/Assets/Asset.h"

#include "Assets/BinaryFormats/AudioData.h"
#include "Assets.Core.hpp"

namespace Eclipse::Assets
{
	struct ASSET_API AudioClip : public Asset<AudioData> {
		ASSET_IMPL(AudioClip, AudioData)

	public:
	};
}