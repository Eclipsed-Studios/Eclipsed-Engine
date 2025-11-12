#pragma once

#include "EntityEngine/Components/Base/BaseComponent.h"

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