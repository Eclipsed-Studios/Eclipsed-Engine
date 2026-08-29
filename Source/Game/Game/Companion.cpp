#include "Companion.h"

#include "Input/Input.h"
#include "Core/Timer.h"
#include "EclipsedEngine/Components/Rendering/SpriteRenderer2D.h"
#include "EclipsedEngine/Components/Transform2D.h"

#include "PlayerMovement.h"

#include "Companion/CompanionInteractableManager.h"

void Companion::Start()
{
	targetInteractable = CompanionInteractableManager::GetClosestInteractable(PlayerMovement::Pos);
}

void Companion::Update()
{
	if (targetInteractable == nullptr)
	{
		targetPos = PlayerMovement::Pos;
		TargetingInteractable = false;
	}
	else
	{
		auto interactable = CompanionInteractableManager::GetClosestInteractable(PlayerMovement::Pos);
		if (interactable->gameObject->transform->GetPosition().Distance(PlayerMovement::Pos) < toInteractableThreshhold)
		{
			targetInteractable = interactable;
			targetPos = targetInteractable->gameObject->transform->GetPosition();
			TargetingInteractable = true;
		}

		if (interactable->gameObject->transform->GetPosition().Distance(gameObject->transform->GetPosition()) < 0.1f && interactable->interactWhenClose)
		{
			interactable->Enable();
			targetInteractable = nullptr;
		}
	}

	float dt = Eclipse::Core::Timer::GetDeltaTime();
	time += dt;

	float px = targetPos.x;
	float py = targetPos.y;

	float xOffset =
		std::sin(time * horizontalSpeed) * horizontalAmplitude +
		std::sin(time * horizontalSecondarySpeed) * horizontalSecondaryAmplitude;

	float yOffset =
		std::sin(time * verticalSpeed) * verticalAmplitude +
		std::sin(time * verticalSecondarySpeed) * verticalSecondaryAmplitude;

	float xTarget = px + xOffset;


	float yTarget = py + yOffset;

	if (!TargetingInteractable)
		yTarget += headOffset;

	float cx = gameObject->transform->GetPosition().x;
	float cy = gameObject->transform->GetPosition().y;

	float x = std::lerp(cx, xTarget, dt);
	float y = std::lerp(cy, yTarget, dt);

	gameObject->transform->SetPosition({ x, y });
}