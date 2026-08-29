#pragma once

#include "EclipsedEngine/Components/Component.h"

#include "Core/Math/Vector/Vector2.h"

class Player : public Eclipse::Component
{
	COMPONENT_BASE_2(Player, 0)

public:
	void Start() override;

	void Reset();

private:
	Eclipse::Math::Vector2f CurrentCheckpointPosition;
};