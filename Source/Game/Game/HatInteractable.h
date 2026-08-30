#pragma once

#include "Interactable.h"

class HatInteractable : public Interactable
{
	COMPONENT_BASE_2(HatInteractable, 0);

public:
	void OnTriggerEnter(Eclipse::GameObject* Other) override;
	void OnTriggerExit(Eclipse::GameObject* Other) override;

	void Interact() override;
	void Update() override;

	void Start() override;

private:
	float StartPositionY;

	float timer;

	SERIALIZED_FIELD_DEFAULT(float, floatSpeed, 0.3f);
	SERIALIZED_FIELD_DEFAULT(float, floatForce, 0.3f);
};