#include "SmoothCameraMover.h"

#include "Input/Input.h"

#include "Core/Math/Vector/Vector2.h"

#include "EclipsedEngine/ECS/ECS_Component.h"

#include "EclipsedEngine/Components/Transform2D.h"

#include "ECS/ComponentManager.h"

#include "Core/Math/CommonMath.h"
#include "Core/Timer.h"

#include "EclipsedEngine/Components/Physics/RigidBody2D.h"

void SmoothCameraMover::Start()
{
	PlayerObject = Eclipse::ComponentManager::FindObjectByName("Player");
	PlayerRigidBody = PlayerObject->GetComponent<Eclipse::RigidBody2D>();
}

void SmoothCameraMover::Update()
{
	float deltatime = Eclipse::Core::Timer::GetDeltaTime();


	Eclipse::Math::Vector2f PlayerPosition = PlayerObject->transform->GetPosition();
	Eclipse::Math::Vector2f PlayerVelocity = PlayerRigidBody->GetVelocity();
	
	Eclipse::Math::Vector2f TargetPosition = PlayerPosition + PlayerVelocity * SmoothDistance;

	float SmoothTime = deltatime * SmoothSpeed;
	Eclipse::Math::Vector2f CameraPosition = gameObject->transform->GetPosition();
	float xPos = Eclipse::Math::Lerp(CameraPosition.x, TargetPosition.x, SmoothTime);
	float yPos = Eclipse::Math::Lerp(CameraPosition.y, TargetPosition.y, SmoothTime);

	Eclipse::Math::Vector2f FinalPosition(xPos, yPos);

	gameObject->transform->SetPosition(FinalPosition);
}
