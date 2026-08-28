#include "PlayerMovement.h"

#include "Core/Math/Vector/Vector2.h"

#include "Core/Timer.h"
#include "Input/Input.h"

#include "EclipsedEngine/Components/Physics/RigidBody2D.h"
#include "EclipsedEngine/Components/Transform2D.h"

#include "SquishAnimator.h"

#include "Physics/PhysicsEngine.h"


void PlayerMovement::Start()
{
	rb = gameObject->GetComponent<Eclipse::RigidBody2D>();
	AudioEmitter = gameObject->GetComponent<Eclipse::AudioEmitter>();
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

	Pos = gameObject->transform->GetPosition();

	JumpLogic();
}

bool PlayerMovement::IsGrounded()
{
	Eclipse::HitResults HitResults;
	Eclipse::PhysicsEngine::OverlapSphere(Pos - GroundcheckOffset, 0.0475f, HitResults);

	for (auto& Result : HitResults.results)
	{
		Eclipse::GameObject* otherGameObjects = Eclipse::ComponentManager::GetGameObject(Result.gameobject);
		PlayerMovement* IsPlayerMovement = otherGameObjects->GetComponent<PlayerMovement>();
		if (IsPlayerMovement)
			continue;

		return true;
	}

	return false;
}

void PlayerMovement::JumpLogic()
{
	bool isgrounded = IsGrounded();

	if (isgrounded && Eclipse::Input::GetKeyDown(Eclipse::Keycode::SPACE))
	{
		float CurrentVelocityY = rb->GetVelocity().x;

		Eclipse::Math::Vector2f force = { CurrentVelocityY, JumpForce };
		rb->SetVelocity(force);

		AudioEmitter->Play();

		if (auto anim = gameObject->GetComponent<SquishAnimator>())
		{
			anim->StartSquish();
		}
	}
}
