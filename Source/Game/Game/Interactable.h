#pragma once

#include "EclipsedEngine/Components/Component.h"

class Interactable : public Eclipse::Component
{
	COMPONENT_BASE_2(Interactable, 0);

public:
	virtual void Interact() {}

private:
	
};