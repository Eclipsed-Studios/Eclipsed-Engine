#include "CompanionInteractable.h"

#include "ECS/ComponentManager.h"
#include "Companion/CompanionInteraction.h"

#include "CompanionInteractableManager.h"

#include "EclipsedEngine/Components/Rendering/SpriteRenderer2D.h"

#include <vector>

#include "EventBroadcaster.h"

void CompanionInteractable::Start()
{
	OffSprite = gameObject->GetChild(0)->GetComponent<Eclipse::SpriteRenderer2D>()->GetSprite();
	CompanionInteractableManager::AddInteractable(this);


}

void CompanionInteractable::Enable()
{
	gameObject->GetChild(0)->GetComponent<Eclipse::SpriteRenderer2D>()->SetSprite(OnSprite);

	Eclipse::GameObject* obj = Eclipse::ComponentManager::FindObjectByName(objectInteractName->c_str());
	if (obj)
	{
		std::vector<CompanionInteraction*> CompanionInteractables;
		obj->GetComponents<CompanionInteraction>(CompanionInteractables);

		for (auto& Interactable : CompanionInteractables)
			Interactable->Interact();
	}

	Eclipse::GameObject* obj1 = Eclipse::ComponentManager::FindObjectByName(SecondaryObjectInteractName->c_str());
	if (obj1)
	{
		std::vector<CompanionInteraction*> CompanionInteractables;
		obj1->GetComponents<CompanionInteraction>(CompanionInteractables);

		for (auto& Interactable : CompanionInteractables)
			Interactable->Interact();
	}
}

void CompanionInteractable::Update()
{
	if (!ResetOnDeath)
		return;

	if (EventBroadcaster::Listen("Death"))
	{
		gameObject->GetChild(0)->GetComponent<Eclipse::SpriteRenderer2D>()->SetSprite(OffSprite);
	}
}

void CompanionInteractable::OnDestroy()
{
	CompanionInteractableManager::Reset();
}
