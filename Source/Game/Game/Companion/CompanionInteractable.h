#pragma once

#include "EclipsedEngine/Components/Component.h"

class CompanionInteractable : public Eclipse::Component
{
	COMPONENT_BASE_2(CompanionInteractable, 0);
public:
	void Start() override;
	void Enable();

	void OnDestroy() override;

	SERIALIZED_FIELD_DEFAULT(bool, interactWhenClose, false);
private:
	SERIALIZED_FIELD_DEFAULT(std::string, objectInteractName, "");
};