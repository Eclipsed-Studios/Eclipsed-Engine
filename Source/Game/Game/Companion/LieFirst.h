#pragma once

#include "CompanionInteraction.h"

class LieFirst : public CompanionInteraction
{
	COMPONENT_BASE_2(LieFirst, 0);
public:
	void Interact() override;

	void Update() override;

private:
	bool hasTricked = false;
};