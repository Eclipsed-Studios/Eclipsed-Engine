#include "AudioSource.h"

namespace ENGINE_NAMESPACE
{
    void AudioSource::SetAudioClip(const char* aPath)
    {
        myAudioClip = Resources::Get<AudioClip>(aPath);
    }

    void AudioSource::Play()
    {
        if (!myIsPlaying) 
        {
            AudioManager::PlayAudio(*myAudioClip.Get());
            myIsPlaying = true;
        }
        else if (myIsPaused)
        {
            myIsPaused = !myIsPaused;
            myAudioClip->myChannel->setPaused(myIsPaused);
        }
    }

    void AudioSource::Pause()
    {
        myIsPaused = true;
        myAudioClip->myChannel->setPaused(true);
    }

    void AudioSource::Stop()
    {
        myAudioClip->myChannel->stop();
        myAudioClip->myChannel = nullptr;

        myIsPlaying = false;
    }
}