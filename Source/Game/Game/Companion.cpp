#include "Companion.h"

#include "Input/Input.h"
#include "Core/Timer.h"
#include "EclipsedEngine/Components/Rendering/SpriteRenderer2D.h"
#include "EclipsedEngine/Components/Transform2D.h"

#include "PlayerMovement.h"

#include "Companion/CompanionInteractableManager.h"

#include "EventBroadcaster.h"

void Companion::Start()
{
	EventBroadcaster::Clear();
	targetInteractable = nullptr;
	returningToPlayer = false;
	TargetingInteractable = false;
}

void Companion::Update()
{
	// ---------------------------------------------------------
	// Going to an interactable
	// ---------------------------------------------------------
	if (targetInteractable != nullptr)
	{
		TargetingInteractable = true;

		targetPos = targetInteractable->gameObject->transform->GetPosition();

		float distance =
			targetPos.Distance(gameObject->transform->GetPosition());

		if (distance < 0.1f)
		{
			if (targetInteractable->waitForEvent)
			{
				if (EventBroadcaster::Listen(targetInteractable->waitForEventName))
				{
					canInteract = true;
				}
			}
			else
			{
				canInteract = true;
			}

			if (canInteract)
			{
				targetInteractable->Enable();
				CompanionInteractableManager::RemoveTarget(targetInteractable);

				targetInteractable = nullptr;

				// Now go back to the player.
				returningToPlayer = true;
				TargetingInteractable = false;
				canInteract = false;
			}
		}
	}
	// ---------------------------------------------------------
	// Returning to player
	// ---------------------------------------------------------
	else if (returningToPlayer)
	{
		TargetingInteractable = false;
		targetPos = PlayerMovement::Pos;

		float distance =
			targetPos.Distance(gameObject->transform->GetPosition());

		if (distance < 0.5f)
		{
			returningToPlayer = false;
		}
	}
	// ---------------------------------------------------------
	// Following player / looking for an interactable
	// ---------------------------------------------------------
	else
	{
		TargetingInteractable = false;
		targetPos = PlayerMovement::Pos;

		auto interactable =
			CompanionInteractableManager::GetClosestInteractable(PlayerMovement::Pos);

		if (interactable != nullptr)
		{
			float distance =
				interactable->gameObject->transform->GetPosition()
				.Distance(PlayerMovement::Pos);

			if (distance < toInteractableThreshhold)
			{
				targetInteractable = interactable;
				TargetingInteractable = true;
				targetPos = targetInteractable->gameObject->transform->GetPosition();
			}
		}
	}

	// ---------------------------------------------------------
	// Movement
	// ---------------------------------------------------------
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