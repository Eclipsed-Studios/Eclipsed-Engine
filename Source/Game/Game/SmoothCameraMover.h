#pragma once

#include "EclipsedEngine/Components/Component.h"

namespace Eclipse
{
	class RigidBody2D;
}

class SmoothCameraMover : public Eclipse::Component
{
	COMPONENT_BASE_2(SmoothCameraMover, 0)

public:
	void Update() override;
	void Start() override;

private:
	Eclipse::GameObject* PlayerObject;
	Eclipse::RigidBody2D* PlayerRigidBody;

	SERIALIZED_FIELD_DEFAULT(float, SmoothSpeed, 1.f);
	SERIALIZED_FIELD_DEFAULT(float, SmoothDistance, 1.f);
};