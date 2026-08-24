#pragma once

#include "EclipsedEngine/Components/Component.h"

class ParallaxBackground : public Eclipse::Component
{
	COMPONENT_BASE_2(ParallaxBackground, 0);

public:
	void Start() override;

private:
	SERIALIZED_FIELD(Eclipse::Assets::Prefab, testSpawn);
};