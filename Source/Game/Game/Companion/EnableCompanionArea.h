#pragma once

#include "EclipsedEngine/Components/Component.h"

class EnableCompanionArea : public Eclipse::Component
{
	COMPONENT_BASE_2(EnableCompanionArea, 0);

public:
	void OnTriggerEnter(Eclipse::GameObject* Other) override;

private:
	SERIALIZED_FIELD(Eclipse::Assets::Prefab, companionPrefab);
};