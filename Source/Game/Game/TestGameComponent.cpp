#include "TestGameComponent.h"

#include "Core/Timer.h"
#include "ECS/GameObject.h"
#include "ECS/ComponentManager.h"

#include "Input/Input.h"

#include "EclipsedEngine/Components/Physics/RigidBody2D.h"

void TestGameComponent::Start()
{
	rb = gameObject->GetComponent<Eclipse::RigidBody2D>();
}

void TestGameComponent::Update()
{
	values = Eclipse::Core::Timer::GetDeltaTime();
	totalTime = Eclipse::Core::Timer::GetTotalTime();

	if (Eclipse::Input::GetKeyDown(Eclipse::Keycode::SPACE))
	{
		Eclipse::Math::Vector2f force = { 0.f, upForce };
		rb->AddForce(force);
	}
}
