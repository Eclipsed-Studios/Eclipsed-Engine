#include "PlayerMovement.h"

#include "Core/Math/Vector/Vector2.h"

#include "Core/Timer.h"
#include "Input/Input.h"

#include "EclipsedEngine/Components/Physics/RigidBody2D.h"
#include "EclipsedEngine/Components/Transform2D.h"

#include "SquishAnimator.h"


void PlayerMovement::Start()
{
	rb = gameObject->GetComponent<Eclipse::RigidBody2D>();
}

void PlayerMovement::Update()
{
	float deltatime = Eclipse::Core::Timer::GetDeltaTime();

	bool InputRight = Eclipse::Input::GetKey(Eclipse::Keycode::A);
	bool InputLeft = Eclipse::Input::GetKey(Eclipse::Keycode::D);

	int HorizontalMovement = static_cast<int>(InputLeft) - static_cast<int>(InputRight);
	float HorizontalMovementFloat = static_cast<float>(HorizontalMovement) * MaxMovespeed;

	float CurrentVelocityY = rb->GetVelocity().y;

	Eclipse::Math::Vector2f velocity(HorizontalMovementFloat, CurrentVelocityY);

	rb->SetVelocity(velocity);

	if (Eclipse::Input::GetKeyDown(Eclipse::Keycode::SPACE))
	{
		Eclipse::Math::Vector2f force = { 0.f, JumpForce };
		rb->AddForce(force);

		if (auto anim = gameObject->GetComponent<SquishAnimator>())
		{
			anim->StartSquish();
		}
	}

	Pos = gameObject->transform->GetPosition();
}
