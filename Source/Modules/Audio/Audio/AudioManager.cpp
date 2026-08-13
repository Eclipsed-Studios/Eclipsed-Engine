#include "AudioManager.h"

#include "fmod/fmod.hpp"

#include "Core/MainSingleton.h"

#include <filesystem>
#include <iostream>

namespace Eclipse
{
    FMOD::ChannelGroup* AudioManager::masterGroup;
    FMOD::ChannelGroup* AudioManager::musicGroup;
    FMOD::ChannelGroup* AudioManager::sfxGroup;
    FMOD::ChannelGroup* AudioManager::uiGroup;
    FMOD::ChannelGroup* AudioManager::ambientGroup;
    FMOD::ChannelGroup* AudioManager::voiceGroup;

	FMOD::System* AudioManager::mySystem;
	FMOD::Studio::System* AudioManager::myStudioSystem;

	void AudioManager::Init()
	{
        FMOD_RESULT result;

        result = FMOD::Studio::System::create(&myStudioSystem);
        if (result != FMOD_OK) {
            return;
        }

        result = myStudioSystem->initialize(
            512,
            FMOD_STUDIO_INIT_NORMAL,
            0,
            nullptr
        );
        if (result != FMOD_OK) {
            return;
        }


        result = FMOD::System_Create(&mySystem);
        if (result != FMOD_OK) {
            return;
        }

        result = mySystem->setSoftwareFormat(48000, FMOD_SPEAKERMODE_STEREO, 0);
        if (result != FMOD_OK) {
            return;
        }

        result = mySystem->init(
            512, 0, nullptr
        );
        if (result != FMOD_OK) {
            return;
        }

        result = mySystem->set3DSettings(1.0f, 2.0f, 0.5f);
        if (result != FMOD_OK) {
            return;
        }





        { // Make sure the system is correctly setup.
            unsigned version = 0;
            result = mySystem->getVersion(&version);

            if (result != FMOD_OK) {
                return;
            }
        }


        {
            mySystem->createChannelGroup("master", &masterGroup);
            mySystem->createChannelGroup("music", &musicGroup);
            mySystem->createChannelGroup("sfx", &sfxGroup);
            mySystem->createChannelGroup("ui", &uiGroup);
            mySystem->createChannelGroup("ambient", &ambientGroup);
            mySystem->createChannelGroup("voice", &voiceGroup);

            masterGroup->addGroup(musicGroup);
            masterGroup->addGroup(sfxGroup);
            masterGroup->addGroup(uiGroup);
            masterGroup->addGroup(ambientGroup);
            masterGroup->addGroup(voiceGroup);
        }

		MainSingleton::AddInstance<FMOD::System*>(mySystem);
		MainSingleton::AddInstance<FMOD::Studio::System*>(myStudioSystem);
	}

	void AudioManager::Update()
	{
		myStudioSystem->update();
        mySystem->update();
	}

	void AudioManager::PlayAudio(FMOD::Sound* aSound, FMOD::Channel** aChannel)
	{
        if (*aChannel)
        {
            (*aChannel)->stop();
            *aChannel = nullptr;
        }

		mySystem->playSound(aSound, nullptr, false, aChannel);
	}

    FMOD::ChannelGroup* AudioManager::GetBus(AudioBus bus)
    {
        switch (bus)
        {
        case AudioBus::Master:
            return masterGroup;

        case AudioBus::Music:
            return musicGroup;

        case AudioBus::SFX:
            return sfxGroup;

        case AudioBus::UI:
            return uiGroup;

        case AudioBus::Ambient:
            return ambientGroup;

        case AudioBus::Voice:
            return voiceGroup;
        }

        return nullptr;
    }
}
