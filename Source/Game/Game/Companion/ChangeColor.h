#pragma once

#include "CompanionInteraction.h"

class ChangeColor : public CompanionInteraction
{
	COMPONENT_BASE_2(ChangeColor, 0);
public:
	void Interact() override;

private:
	SERIALIZED_FIELD(Eclipse::Math::Color, NewColor);
};