#pragma once

#include "Component.h"

#include <Math/Vector/Vector2.h>

#include <vector>
#include <functional>

#include "AssetManagement/ResourcePointer.h"
#include "AssetManagement/Resources/AudioClip.h"

namespace ENGINE_NAMESPACE
{
	class AudioSource : public Component
	{
	public:
		void SetAudioClip(const char* aPath);

	public:
		void Play();
		void Pause();
		void Stop();

	private:
		ResourcePointer<AudioClip> myAudioClip;
		bool myIsPaused = false;
		bool myIsPlaying = false;
    };
}