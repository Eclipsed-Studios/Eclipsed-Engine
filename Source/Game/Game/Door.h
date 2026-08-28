#pragma once

#include "EclipsedEngine/Components/Component.h"

namespace Eclipse
{
	class SpriteRenderer2D;
}

class Door : public Eclipse::Component
{
	COMPONENT_BASE_2(Door, 0);

public:
	void Start() override;
	void Update() override;

	void Open();
	void Close();

	bool IsOpen() const;

private:
	void UpdateDoorState();

	static void OpenDoor(const std::string& doorName);

private:
	SERIALIZED_FIELD(Eclipse::Math::Color, lightOnColor);
	SERIALIZED_FIELD(Eclipse::Math::Color, lightOffColor);
	SERIALIZED_FIELD_DEFAULT(float, moveDuration, 0.05f);



	enum class DoorState
	{
		Open, Closed
	} targetState = DoorState::Closed, doorState;

	Eclipse::Transform2D* moverTransform;
	Eclipse::Transform2D* colliderTransform;

	Eclipse::SpriteRenderer2D* lightRenderer;

	float moveTimer = 0.f;

	float startY = -0.175f;
	float targetY = 0.0f;

	float maxMoverY = 0.135f;
	float minMoverY = -0.175f;
};