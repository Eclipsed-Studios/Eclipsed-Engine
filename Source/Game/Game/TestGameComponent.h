#pragma once

#include "EclipsedEngine/Components/Component.h"

namespace Eclipse
{
	class RigidBody2D;
}

class TestGameComponent : public Eclipse::Component
{
	COMPONENT_BASE_2(TestGameComponent, 50)

public:
	void Start() override;
	void Update() override;

private:
	Eclipse::RigidBody2D* rb = nullptr;

	SERIALIZED_FIELD(float, upForce);
	SERIALIZED_FIELD(float, values);
	SERIALIZED_FIELD(float, totalTime);
};