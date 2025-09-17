#pragma once

#include "Components/Base/BaseComponent.h"

#include "Math/Rect.h"

#include "ECS/ComponentManager.h"

namespace Eclipse
{
	class UIButton : public Component
	{
		BASE_SELECTION(UIButton, 0)

	public:
		void Update() override;

	public:
		//Math::Rect myRect;
	};
}