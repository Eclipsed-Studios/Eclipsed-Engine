#pragma once

#include <vector>
#include <functional>

#include "EntityEngine/Components/Base/BaseComponent.h"
#include "EntityEngine/ComponentManager.h"

#include <Utilities/Math/Vector/Vector2.h>

namespace Eclipse
{
	namespace Editor
	{
		class InspectorWindow;
	}

	class AudioSource : public Component
	{
		BASE_SELECTION(AudioSource, 0)
    };
}