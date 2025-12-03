#include "AudioManager.h"

#include "fmod/fmod.hpp"

namespace Eclipse
{
	/*void AudioManager::Init() 
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

    void AudioManager::CreateAudioFromPath(AudioClip& anAudioClip)
    {
        FMOD_MODE mode = true ? FMOD_LOOP_NORMAL : FMOD_DEFAULT;

        std::string path = (PathManager::GetAssetDir() / std::string(anAudioClip.GetRelativePath())).generic_string();
        mySystem->createSound(path.c_str(), mode, nullptr, &anAudioClip.mySound);
    }

    void AudioManager::CreateAudioFromMemory(const char* data, size_t size, AudioClip& anAudioClip)
    {
        FMOD_MODE mode = true ? FMOD_LOOP_NORMAL : FMOD_DEFAULT;

        FMOD_CREATESOUNDEXINFO exinfo = {};
        exinfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
        exinfo.length = size;

        mySystem->createSound((const char*)data, FMOD_OPENMEMORY | mode, &exinfo, &anAudioClip.mySound);

    }*/
}
