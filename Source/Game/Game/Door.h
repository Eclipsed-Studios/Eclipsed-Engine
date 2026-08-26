#pragma once

#include "EclipsedEngine/Components/Component.h"

namespace Eclipse
{
	class SpriteRenderer2D;
}

class Door : public Eclipse::Component
{
	COMPONENT_BASE_2(Door, 0);

public:
	void Start() override;
	void Update() override;

private:
	SERIALIZED_FIELD(Eclipse::Math::Color, lightOnColor);

	bool isOpen = false;

	Eclipse::Transform2D* moverTransform;
	Eclipse::Transform2D* colliderTransform;

	Eclipse::SpriteRenderer2D* lightRenderer;

	float maxMoverY = 0.207f;
};