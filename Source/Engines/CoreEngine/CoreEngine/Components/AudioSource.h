#pragma once

#include "Component.h"
#include "ECS/ComponentManager.h"

#include <Math/Vector/Vector2.h>

#include <vector>
#include <functional>

#include "AssetManagement/ResourcePointer.h"
#include "AssetManagement/Resources/AudioClip.h"

namespace ENGINE_NAMESPACE
{
	namespace Editor
	{
		class InspectorWindow;
	}

	class AudioSource : public Component
	{
		BASE_COMPONENT(AudioSource, 0)

	public:
		void SetAudioClip(const char* aPath);

	public:
		void SetVolume(float aVolume);

		void Play();
		void Pause();
		void Stop();

		void SetLooping(bool aState);

	protected:
		void DrawInspector() override;


	private:
		ResourcePointer<AudioClip> myAudioClip;
		bool myIsPaused = false;
		bool myIsPlaying = false;

		bool myIsLooping = false;
		bool myPlayOnStart  = false;

		float myVolume = 1.f;
    };
}