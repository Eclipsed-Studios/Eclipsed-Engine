#pragma once

#include "EclipsedEngine/Components/Component.h"

#include "EntityEngine/ComponentManager.h"

namespace Eclipse
{
	class Button : public Component
	{
		BASE_SELECTION(Button, 0)

	public:
		void Update() override;
	};
}