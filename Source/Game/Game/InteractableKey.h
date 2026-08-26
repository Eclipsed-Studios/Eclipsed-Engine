#pragma once

#include "Interactable.h"

class InteractableKey : public Interactable
{
	COMPONENT_BASE_2(InteractableKey, 0);

public:
	void Interact() override;

private:
	
};