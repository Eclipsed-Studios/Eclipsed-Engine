#pragma once

#include "EclipsedEngine/Components/Component.h"

class ChangePlayerValuesOnTrigger : public Eclipse::Component
{
	COMPONENT_BASE_2(ChangePlayerValuesOnTrigger, 0);

public:
	void OnCollisionEnter(Eclipse::GameObject* OtherGameObject) override;

private:
	
};