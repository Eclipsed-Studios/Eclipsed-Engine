#include "CompanionInteractableManager.h"
#include "EclipsedEngine/Components/Transform2D.h"

void CompanionInteractableManager::AddInteractable(CompanionInteractable* interactable)
{
    interactables.push_back(interactable);
}


CompanionInteractable* CompanionInteractableManager::GetClosestInteractable(const Eclipse::Math::Vector2f& playerPos)
{
	float dst = FLT_MAX;
	CompanionInteractable* companion;

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
