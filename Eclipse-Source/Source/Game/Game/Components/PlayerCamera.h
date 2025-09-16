#pragma once

#include "Components/Base/BaseComponent.h"

namespace Eclipse
{
	class PlayerCamera : public Component
	{
		BASE_SELECTION(PlayerCamera, 0)

	public:
		void Update() override;
        void Awake() override;

		SERIALIZED_FIELD(unsigned, myPlayerGO);
	private:
		class Transform2D* myPlayerTransform = nullptr;
		class Transform2D* myTransform = nullptr;

		float myPositionX = 0.f;
		float myPositionY = 0.f;
	};
}