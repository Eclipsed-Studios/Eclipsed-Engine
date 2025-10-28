#pragma once

#include "Components/Base/BaseComponent.h"

#include "ECS/ComponentManager.h"

namespace Eclipse
{
	class Button : public Component
	{
		BASE_SELECTION(Button, 0)

	public:
		void Update() override;
	};
}