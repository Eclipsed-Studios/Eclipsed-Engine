#pragma once

#include "Components/Base/BaseComponent.h"
#include <string>
#include "Reflection/ReflectionDefines.h"

namespace Eclipse
{
	class PlayerMovement : public Component
	{
		BASE_SELECTION(PlayerMovement, 0)

	public:
		void Awake() override;
		void Update() override;


	private:
		class RigidBody2D* myRigidBody = nullptr;
		class Transform2D* myTransform = nullptr;
		class Player* myPlayer = nullptr;

		const float Run_Multiplier = 1.4f;

		ReflectedVar_Default(float, myJumpStrength, 2.f);
		ReflectedVar_Default(float, myMovementSpeed, 0.4f);
	};
}