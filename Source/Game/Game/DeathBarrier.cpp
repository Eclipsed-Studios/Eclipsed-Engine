#include "DeathBarrier.h"

#include "ECS/ComponentManager.h"

#include "Player.h"

void DeathBarrier::OnTriggerEnter(Eclipse::GameObject* OtherGameObject)
{
	Player* PlayerComponent = OtherGameObject->GetComponent<Player>();
	if (!PlayerComponent)
		return;

	PlayerComponent->Reset();
}
