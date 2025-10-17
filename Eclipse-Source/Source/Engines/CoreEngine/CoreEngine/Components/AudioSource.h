#pragma once

#include <vector>
#include <functional>

#include "Components/Base/BaseComponent.h"
#include "ECS/ComponentManager.h"

#include <Utilities/Math/Vector/Vector2.h>

#include "AssetManagement/ResourcePointer.h"
#include "AssetManagement/Resources/AudioClip.h"

namespace Eclipse
{
	namespace Editor
	{
		class InspectorWindow;
	}

	class AudioSource : public Component
	{
		BASE_SELECTION(AudioSource, 0)

	public:
		void Awake() override;

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
		FMOD::Channel* myChannel;

		ResourcePointer<AudioClip> myAudioClip;
		bool myIsPaused = false;
		bool myIsPlaying = false;


		SERIALIZED_FIELD_DEFAULT_MIN_MAX(float, myVolume, 1.f, 0.f, 1.f);
		SERIALIZED_FIELD_DEFAULT(bool, myPlayOnStart, false);
		SERIALIZED_FIELD_DEFAULT(bool, myIsLooping, false);
		PRIVATE_SERIALIZED_FIELD_DEFAULT(std::string, myAudioPath, "");
    };
}