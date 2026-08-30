#pragma once

#include "EclipsedEngine/Components/Component.h"

class CompanionInteractable : public Eclipse::Component
{
	COMPONENT_BASE_2(CompanionInteractable, 0);
public:
	void Start() override;
	void Enable();

	void Update();

	void OnDestroy() override;

	SERIALIZED_FIELD(Eclipse::Assets::Texture, OnSprite);

	SERIALIZED_FIELD_DEFAULT(bool, ActivatedMultipleTimes, false);

	SERIALIZED_FIELD_DEFAULT(bool, interactWhenClose, false);
	SERIALIZED_FIELD_DEFAULT(bool, waitForEvent, false);

	SERIALIZED_FIELD_DEFAULT(bool, ResetOnDeath, false);
	
	SERIALIZED_FIELD_DEFAULT(std::string, waitForEventName, "");

private:
	SERIALIZED_FIELD_DEFAULT(std::string, objectInteractName, "");
	SERIALIZED_FIELD_DEFAULT(std::string, SecondaryObjectInteractName, "");

	Eclipse::Assets::Texture OffSprite;
};