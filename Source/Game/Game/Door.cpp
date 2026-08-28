#include "Door.h"

#include "Input/Input.h"
#include "Core/Timer.h"
#include "EclipsedEngine/Components/Rendering/SpriteRenderer2D.h"
#include "EclipsedEngine/Components/Transform2D.h"

#include "Core/EventSystem/EventSystem.h"

void Door::Start()
{
	for (auto child : gameObject->GetChildren())
	{
		const std::string name = child->GetName();
		if (name == "Light")
		{
			lightRenderer = child->GetComponent<Eclipse::SpriteRenderer2D>();
		}
		else if (name == "Mover")
		{
			moverTransform = child->transform;

			auto pos = moverTransform->GetPosition();
			moverTransform->SetPosition({ pos.x, -0.175f });

			startY = -0.175f;
			targetY = -0.175f;
		}
		else if (name == "Collider")
		{
			colliderTransform = child->transform;
		}
	}
}

void Door::Update()
{
	UpdateDoorState();
}

void Door::Open()
{
	targetState = DoorState::Open;

	startY = moverTransform->GetPosition().y;
	targetY = maxMoverY;
	moveTimer = 0.0f;
}

void Door::Close()
{
	targetState = DoorState::Closed;

	startY = moverTransform->GetPosition().y;
	targetY = minMoverY;
	moveTimer = 0.0f;
}

bool Door::IsOpen() const
{
	return doorState == DoorState::Open;
}

void Door::UpdateDoorState()
{
	moveTimer += Eclipse::Core::Timer::GetDeltaTime();

	float t = moveTimer / moveDuration;

	if (t > 1.0f)
		t = 1.0f;

	float y = startY + (targetY - startY) * t;

	moverTransform->SetPosition({
		moverTransform->GetPosition().x,
		y
		});

	if (t >= 1.0f)
	{
		doorState = targetState;
	}

	if (targetState == DoorState::Open)
	{
		lightRenderer->SetColor(lightOnColor);
		colliderTransform->SetPosition({ 100000, 10000 });
	}
	else
	{
		lightRenderer->SetColor(lightOffColor);
		colliderTransform->SetPosition({ 0, 0 });
	}
}

void Door::OpenDoor(const std::string& doorName)
{

}
