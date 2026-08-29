#include "BroadcastEventTrigger.h"

#include "EventBroadcaster.h"

void BroadcastEventTrigger::OnTriggerEnter(Eclipse::GameObject* Other)
{
	if (Other->GetName() != "Player")  return;

	EventBroadcaster::Broadcast(event);
}
