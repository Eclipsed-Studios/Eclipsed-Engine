#pragma once

#include "Components/Base/BaseComponent.h"

namespace Eclipse
{
	class PlayerController : public Component
	{
		BASE_SELECTION(PlayerController, 0)

	public:
		void Awake() override;
		void Update() override;


	private:
		class RigidBody2D* myRigidBody = nullptr;
		class Transform2D* myTransform = nullptr;
		class Player* myPlayer = nullptr;

		const float Run_Multiplier = 1.4f;

		SERIALIZED_FIELD_DEFAULT(float, myJumpStrength, 2.f);
		SERIALIZED_FIELD_DEFAULT(float, myMovementSpeed, 0.4f);
	};
}