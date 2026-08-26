#pragma once

#include "EclipsedEngine/Components/Component.h"

class PlayerInteract : public Eclipse::Component
{
	COMPONENT_BASE_2(PlayerInteract, 0);

public:
	void Update() override;

private:
	SERIALIZED_FIELD_DEFAULT(float, Range, 1.f);
};