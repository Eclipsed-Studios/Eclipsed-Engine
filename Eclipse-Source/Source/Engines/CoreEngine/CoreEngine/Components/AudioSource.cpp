#include "AudioSource.h"

#include "Editor/ImGui/ImGui_Impl.h"
#include <sstream>

namespace Eclipse
{
	void AudioSource::Awake()
	{
		SetAudioClip(myAudioPath->c_str());
	}

	void AudioSource::SetAudioClip(const char* aPath)
	{
		myAudioClip = Resources::Get<AudioClip>(aPath);
		myAudioPath = aPath;
	}

	void AudioSource::SetVolume(float aVolume)
	{
		myVolume = aVolume;
		myChannel->setVolume(aVolume);
	}

	void AudioSource::Play()
	{
		if (!myIsPlaying)
		{
			AudioManager::PlayAudio(*myAudioClip.Get(), &myChannel);

			SetVolume(myVolume);
			SetLooping(myIsLooping);

			myIsPlaying = true;
		}
		else if (myIsPaused)
		{
			myIsPaused = !myIsPaused;
			myChannel->setPaused(myIsPaused);
		}
	}

	void AudioSource::Pause()
	{
		myIsPaused = true;
		myChannel->setPaused(true);
	}

	void AudioSource::Stop()
	{
		myChannel->stop();
		myChannel = nullptr;

		myIsPlaying = false;
	}

	void AudioSource::SetLooping(bool aState)
	{
		myIsLooping = aState;

		if (!myAudioClip && !myChannel)  return;

		if (aState) // Play infinitely looping
		{
			myChannel->setMode(FMOD_LOOP_NORMAL);
			myChannel->setLoopCount(-1);
		}
		else // Play once
		{
			myChannel->setMode(FMOD_LOOP_OFF);
			myChannel->setLoopCount(0);
		}
	}
}