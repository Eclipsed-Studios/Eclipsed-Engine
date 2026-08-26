#pragma once

#include "Interactable.h"

class InteractableButton : public Interactable
{
	COMPONENT_BASE_2(InteractableButton, 0);

public:
	void Interact() override;

private:

};