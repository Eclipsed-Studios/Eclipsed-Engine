#pragma once

#include "EclipsedEngine/Components/Component.h"

class ChangePlayerValuesOnTrigger : public Eclipse::Component
{
	COMPONENT_BASE_2(ChangePlayerValuesOnTrigger, 0);

public:
	void OnTriggerEnter(Eclipse::GameObject* OtherGameObject) override;
	void OnTriggerExit(Eclipse::GameObject* OtherGameObject) override;

private:
	float OriginalMaxSpeed = 0;
	float OriginalJumpHeight = 0;

	SERIALIZED_FIELD(bool, ChangeSpeed);
	SERIALIZED_FIELD(bool, ChangeJumpheight);
};