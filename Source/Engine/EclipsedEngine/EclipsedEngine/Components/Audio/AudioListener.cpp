#include "AudioListener.h"

#include "fmod/fmod_studio.h"
#include "fmod/fmod_studio.hpp"

#include "EclipsedEngine/Components/Transform2D.h"

namespace Eclipse
{
	AudioListener* AudioListener::ListenerInstance;

	void AudioListener::Awake()
	{
		gameObject->transform->AddFunctionToRunOnDirtyUpdate(this, [this]() {UpdatePositionalData();});
		ListenerInstance = this;
	}

	AudioListener* AudioListener::GetListener()
	{
		return ListenerInstance;
	}

	// TODO: Fix so it supports rotation and object velocity.
	void AudioListener::UpdatePositionalData()
	{
		FMOD::System* sys = MainSingleton::GetRaw<FMOD::System*>();

		Math::Vector2f ePos = gameObject->transform->GetPosition();

		FMOD_VECTOR pos = { ePos.x, ePos.y, 0.f };
		FMOD_VECTOR vel = { 0.f, 0.f, 0.f };

		FMOD_VECTOR forward = { 0.f, 0.f, 1.f };
		FMOD_VECTOR up = { 0.f, 1.f, 0.f };

		sys->set3DListenerAttributes(0, &pos, &vel, &forward, &up);
	}
}