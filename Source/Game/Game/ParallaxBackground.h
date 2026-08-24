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
	void Start() override;
	void Update() override;

private:
	float startingPosX = 0.f;
	float posY = 0.f;
	float rot = 0.f;
	Eclipse::SpriteRenderer2D* rend;
};

class ParallaxBackground : public Eclipse::Component
{
	COMPONENT_BASE_2(ParallaxBackground, 0);

public:
	void Start() override;

private:
	SERIALIZED_FIELD(Eclipse::Assets::Prefab, testSpawn);
};