#pragma once

#include "EclipsedEngine/Components/Component.h"

class TestGameComponent : public Eclipse::Component
{
	COMPONENT_BASE_2(TestGameComponent, 50)

public:
	void Update() override;

private:
	SERIALIZED_FIELD(float, values);
	SERIALIZED_FIELD(float, totalTime);
};