#pragma once

#include "EclipsedEngine/Components/Component.h"
#include "Core/Math/Vector/Vector2.h"

namespace Eclipse
{
	class RigidBody2D;
}

class PlayerMovement : public Eclipse::Component
{
	COMPONENT_BASE_2(PlayerMovement, 0)

public:
	void Start() override;
	void Update() override;

	bool IsGrounded();
	void JumpLogic();

public:
	SERIALIZED_FIELD(float, MaxMovespeed);

private:
	Eclipse::RigidBody2D* rb = nullptr;

	SERIALIZED_FIELD(float, Acceleration);
	float Movespeed;

	SERIALIZED_FIELD(float, JumpForce);

public:
	static inline Eclipse::Math::Vector2f Pos = {};

	SERIALIZED_FIELD(Eclipse::Math::Vector2f, GroundcheckOffset);
};