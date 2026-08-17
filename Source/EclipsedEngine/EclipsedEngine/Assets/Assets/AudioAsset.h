#pragma once

#include "EclipsedEngine/Assets/Asset.h"

#include "EclipsedEngine/Assets/BinaryFormats/AudioData.h"

namespace Eclipse::Assets
{
	struct AudioClip : public Asset<AudioData> {
		ASSET_IMPL(AudioClip, AudioData)

	public:
	};
}