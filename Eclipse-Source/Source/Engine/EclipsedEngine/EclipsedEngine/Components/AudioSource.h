#pragma once

#include <vector>
#include <functional>
	
#include "EntityEngine/BaseComponent.h"
#include "EntityEngine/ComponentManager.h"

#include <CoreEngine/Math/Vector/Vector2.h>

namespace Eclipse
{
	namespace Editor
	{
		class InspectorWindow;
	}

	class AudioSource : public Component
	{
		COMPONENT_BASE_2(AudioSource, 0)
    };
}