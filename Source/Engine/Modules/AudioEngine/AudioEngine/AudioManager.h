#pragma once

#include "fmod/fmod.h"
#include "fmod/fmod.hpp"
#include "fmod/fmod_studio.h"
#include "fmod/fmod_studio.hpp"

#include "PcmData.h"

namespace Eclipse
{
	enum class AudioBus
	{
		Master,
		Music,
		SFX,
		UI,
		Ambient,
		Voice
	};

	class AudioManager
	{
	public:
		static void Init();
		static void Update();

		static void PlayAudio(FMOD::Sound* aSound, FMOD::Channel** aChannel);

		static FMOD::ChannelGroup* GetBus(AudioBus bus);

	private:
		static FMOD::ChannelGroup* masterGroup;
		static FMOD::ChannelGroup* musicGroup;
		static FMOD::ChannelGroup* sfxGroup;
		static FMOD::ChannelGroup* uiGroup;
		static FMOD::ChannelGroup* ambientGroup;
		static FMOD::ChannelGroup* voiceGroup;

		static FMOD::System* mySystem;
		static FMOD::Studio::System* myStudioSystem;
	};
}