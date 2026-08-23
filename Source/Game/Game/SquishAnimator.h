#pragma once

#include "EclipsedEngine/Components/Component.h"

class SquishAnimator : public Eclipse::Component
{
	COMPONENT_BASE_2(SquishAnimator, 0);

public:
	void Update() override;
	void Start() override;

	void StartSquish();

	void CollisionStart();

private:
	SERIALIZED_FIELD_DEFAULT(float, SquishTime, 1.f);
	SERIALIZED_FIELD_DEFAULT(float, SquishAmount, 1.f);

	bool IsSquishing = false;

	bool RayWasHit = true;
};