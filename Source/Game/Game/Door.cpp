#include "Door.h"

#include "Input/Input.h"
#include "Core/Timer.h"
#include "EclipsedEngine/Components/Rendering/SpriteRenderer2D.h"
#include "EclipsedEngine/Components/Transform2D.h"

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
	if (targetState != DoorState::Open && Eclipse::Input::GetKeyDown(Eclipse::Keycode::J))
	{
		targetState = DoorState::Open;

		startY = moverTransform->GetPosition().y;
		targetY = maxMoverY;
		moveTimer = 0.0f;
	}
	else if (targetState != DoorState::Closed &&  Eclipse::Input::GetKeyDown(Eclipse::Keycode::K))
	{
		targetState = DoorState::Closed;

		startY = moverTransform->GetPosition().y;
		targetY = minMoverY;
		moveTimer = 0.0f;
	}

	UpdateDoorState();
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
