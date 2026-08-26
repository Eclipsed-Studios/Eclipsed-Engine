#pragma once

#include "EclipsedEngine/Components/Component.h"

class WorldModifier : public Eclipse::Component
{
	COMPONENT_BASE_2(WorldModifier, 0);

public:
	void ToggleObject();

private:
	SERIALIZED_FIELD(std::string, NameOfObjectToToggle);
};