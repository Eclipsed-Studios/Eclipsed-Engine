#include "IAudioManager.h"

namespace Eclipse::Audio
{
	IAudioDevice* IAudioManager::GetDevice()
	{
		return audioDevice;
	}
}