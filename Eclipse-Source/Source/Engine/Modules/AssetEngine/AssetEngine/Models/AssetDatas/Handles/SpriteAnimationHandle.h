#pragma once

#include "AssetHandle.h"
#include <string>
#include <vector>

namespace Eclipse::Assets
{
	struct SpriteAnimationHandle : public AssetHandle
	{
		std::string AnimationName;
		std::vector<unsigned> Frames;
	};
};