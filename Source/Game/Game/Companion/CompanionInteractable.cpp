#include "CompanionInteractable.h"

#include "ECS/ComponentManager.h"
#include "Companion/CompanionInteraction.h"

#include "CompanionInteractableManager.h"

void CompanionInteractable::Start()
{
	CompanionInteractableManager::AddInteractable(this);
}

void CompanionInteractable::Enable()
{
	Eclipse::GameObject* obj = Eclipse::ComponentManager::FindObjectByName(objectInteractName->c_str());
	if (obj)
	{
		obj->GetComponent<CompanionInteraction>()->Interact();
	}
}

void CompanionInteractable::OnDestroy()
{
	CompanionInteractableManager::Reset();
}
