#include "AudioManager.h"

#include "fmod/fmod/fmod.hpp"


namespace Eclipse
{
	void AudioManager::Init() 
	{
        FMOD_RESULT result;

        result = FMOD::System_Create(&mySystem);
        result = mySystem->init(512, FMOD_INIT_NORMAL, nullptr);
	}

	void AudioManager::Update()
	{
        mySystem->update();
	}

    void AudioManager::PlayAudio(AudioClip& anAudioClip, FMOD::Channel** aChannel)
    {
        mySystem->playSound(anAudioClip.mySound, nullptr, false, aChannel);
    }

    void AudioManager::CreateAudio(AudioClip& anAudioClip)
    {
        FMOD_MODE mode = true ? FMOD_LOOP_NORMAL : FMOD_DEFAULT;

        std::string path = ASSET_PATH + std::string(anAudioClip.GetRelativePath());
        mySystem->createSound(path.c_str(), mode, nullptr, &anAudioClip.mySound);
    }
}
