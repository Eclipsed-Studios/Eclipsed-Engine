#pragma once

#include "AssetHandle.h"
#include "CoreEngine/Math/RectSizePos.h"
#include <vector>

namespace FMOD
{
	struct Sound;
}

namespace Eclipse::Assets 
{
	struct AudioClipHandle : public AssetHandle
	{
		FMOD::Sound* sound;
	};
};