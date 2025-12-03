#pragma once

#include <vector>
#include <functional>
	
#include "EclipsedEngine/Components/Component.h"

#include <CoreEngine/Math/Vector/Vector2.h>

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