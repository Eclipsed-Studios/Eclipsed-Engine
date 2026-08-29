#pragma once

#include "EclipsedEngine/Components/Component.h"

class DeathBarrier : public Eclipse::Component
{
	COMPONENT_BASE_2(DeathBarrier, 0);

public:
	void OnTriggerEnter(Eclipse::GameObject*) override;

private:
};