#pragma once

#include "Asset.h"


namespace Eclipse
{
	namespace Assets
	{
		struct AudioClipHandle;
		class AudioClipManager;
	}

	class AudioClip final
	{
		ASSET_OPERATORS_DEF(AudioClip, Assets::AudioClipHandle, Assets::AudioClipManager);
	};
}