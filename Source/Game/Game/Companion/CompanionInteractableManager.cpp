#include "CompanionInteractableManager.h"
#include "EclipsedEngine/Components/Transform2D.h"

void CompanionInteractableManager::AddInteractable(CompanionInteractable* interactable)
{
    interactables.push_back(interactable);
}

void CompanionInteractableManager::RemoveTarget(CompanionInteractable* interactable)
{
	for (auto it = interactables.begin(); it != interactables.end(); it++)
		if (*it == interactable)
		{
			interactables.erase(it);
			break;
		}
}

CompanionInteractable* CompanionInteractableManager::GetClosestInteractable(const Eclipse::Math::Vector2f& playerPos)
{
	if (interactables.empty()) return nullptr;

	float dst = FLT_MAX;
	CompanionInteractable* companion = nullptr;

	for (auto comp : interactables)
	{
		float curDst = comp->gameObject->transform->GetPosition().Distance(playerPos);

		if (curDst < dst)
		{
			dst = curDst;
			companion = comp;
		}
	}

    return companion;
}

void CompanionInteractableManager::Reset()
{
	interactables.clear();
}
