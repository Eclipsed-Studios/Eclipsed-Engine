#pragma once

#include "CompanionInteraction.h"

class MoveBridge : public CompanionInteraction
{
	COMPONENT_BASE_2(MoveBridge, 0);
public:
	void Interact() override;

	void Update() override;

private:
	SERIALIZED_FIELD(Eclipse::Math::Vector2f, startPos);
	SERIALIZED_FIELD(Eclipse::Math::Vector2f, targetPos);
	SERIALIZED_FIELD(bool, moveBack);

	SERIALIZED_FIELD(float, moveDuration);
	SERIALIZED_FIELD(float, stayDuration);

	bool reachedTarget = false;
	float elapsed = 0.f;
	float stayElapsed = 0.f;
	bool interacted = false;
};