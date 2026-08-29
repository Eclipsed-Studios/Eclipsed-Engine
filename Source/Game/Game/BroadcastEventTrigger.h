#pragma once

#include "EclipsedEngine/Components/Component.h"

class BroadcastEventTrigger : public Eclipse::Component
{
	COMPONENT_BASE_2(BroadcastEventTrigger, 0);

public:
	void OnTriggerEnter(Eclipse::GameObject* Other) override;

	SERIALIZED_FIELD(std::string, event);
};