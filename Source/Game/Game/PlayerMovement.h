#pragma once

#include "EclipsedEngine/Components/Component.h"

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

public:
	SERIALIZED_FIELD(float, MaxMovespeed);

private:
	Eclipse::RigidBody2D* rb = nullptr;

	SERIALIZED_FIELD(float, Acceleration);
	float Movespeed;

	SERIALIZED_FIELD(float, JumpForce);
};