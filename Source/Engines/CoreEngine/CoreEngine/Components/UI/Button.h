#pragma once

#include "Components/Base/BaseComponent.h"

#include "Math/Rect.h"

#include "ECS/ComponentManager.h"

namespace ENGINE_NAMESPACE
{
	class UIButton : public Component
	{
		BASE_SELECTION(UIButton, 0)

	public:
		void Update() override;

		void DrawInspector() override;

	public:
		//Math::Rect myRect;
	};
}