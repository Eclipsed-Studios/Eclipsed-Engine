#pragma once

#include "Math/Vector/Vector2.h"

#include "Abstract/AbstractResource.h"

#include "fmod/fmod/fmod.h"
#include "fmod/fmod/fmod.hpp"

namespace ENGINE_NAMESPACE
{
	class AudioClip : public AbstractResource
	{
		BASE_RESOURCE(AudioClip)

	public:
		friend class AudioManager;

	public:

	public:
		FMOD::Channel* myChannel;
		FMOD::Sound* mySound;
	};
}