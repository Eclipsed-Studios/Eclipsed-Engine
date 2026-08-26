#include "PlayerInteract.h"

#include "INPUT/Input.h"
#include "INPUT/KeyCodes.h"

#include "Physics/PhysicsEngine.h"

#include "EclipsedEngine/Components/Transform2D.h"
#include <EclipsedEngine/DebugLogger.h>

#include "ECS/ComponentManager.h"
#include "ECS/GameObject.h"

#include "Interactable.h"

void PlayerInteract::Update()
{
	Eclipse::HitResults Results;
	bool RangeCheck = Eclipse::PhysicsEngine::OverlapSphere(gameObject->transform->GetPosition(), Range, Results);
	
	if (!RangeCheck)
		return;

	Interactable* InteractableInRange = nullptr;

	for (auto& result : Results.results)
	{
		Eclipse::GameObject* otherGameObject = Eclipse::ComponentManager::GetGameObject(result.gameobject);

		InteractableInRange = otherGameObject->GetComponent<Interactable>();
		if (InteractableInRange)
			break;
	}

	if (!InteractableInRange)
		return;

	if (Eclipse::Input::GetKeyDown(Eclipse::Keycode::E))
	{
		InteractableInRange->Interact();
	}
}