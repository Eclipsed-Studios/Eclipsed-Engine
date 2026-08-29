#include "EnableCompanionArea.h"

#include "EclipsedEngine/ECS/ObjectManager.h"

void EnableCompanionArea::OnTriggerEnter(Eclipse::GameObject* Other)
{
	if (Other->GetName() != "Player")  return;

	Eclipse::GameObject* obj = Eclipse::Instantiate(companionPrefab);
	obj->transform->SetPosition({ 1, 2 });

	Eclipse::ComponentManager::Destroy(gameObject->GetID());
}
