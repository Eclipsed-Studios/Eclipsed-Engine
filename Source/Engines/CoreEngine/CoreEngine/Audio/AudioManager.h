#pragma once

#include "fmod/fmod.h"
#include "fmod/fmod.hpp"

#include "AssetManagement/Resources/AudioClip.h"

namespace Eclipse
{
	class AudioManager
	{
	public:
		static void Init();
		static void Update();

		static void PlayAudio(AudioClip& anAudioClip, FMOD::Channel** aChannel);
		static void CreateAudio(AudioClip& anAudioClip);

	private:
		static inline FMOD::System* mySystem;
	};
}