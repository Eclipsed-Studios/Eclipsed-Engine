#pragma once

#include "EclipsedEngine/Components/Component.h"

class CompanionInteraction : public Eclipse::Component
{
	COMPONENT_BASE_2(CompanionInteraction, 0);
public:
	virtual void Interact() {}
};