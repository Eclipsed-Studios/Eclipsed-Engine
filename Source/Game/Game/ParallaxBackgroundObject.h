#pragma once

#include "EclipsedEngine/Components/Component.h"

namespace Eclipse
{
	class SpriteRenderer2D;
}

class ParallaxBackgroundObject : public Eclipse::Component
{
	COMPONENT_BASE_2(ParallaxBackgroundObject, 0);

public:
	void Awake() override;
	void Update() override;

private:
	SERIALIZED_FIELD_DEFAULT(float, MinZIndex, -200.f);
	SERIALIZED_FIELD_DEFAULT(float, MaxZIndex, -100.f);
	SERIALIZED_FIELD_DEFAULT(float, myZIndex, -150.f);
	SERIALIZED_FIELD_DEFAULT(float, RotationSpeed, 1.f);
	SERIALIZED_FIELD_DEFAULT(bool, DarkenByDepth, false);
	SERIALIZED_FIELD_DEFAULT(bool, Rotate, false);
	SERIALIZED_FIELD_DEFAULT(float, YScaling, 0.3f);
	

private:
	Eclipse::Math::Vector2f startingPos = {};
	float currentRotation = 0.f;

private:
	Eclipse::SpriteRenderer2D* rend;
	float parallax = 0.f;
};