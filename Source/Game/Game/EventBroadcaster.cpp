#include "EventBroadcaster.h"

#include "EclipsedEngine/Components/Rendering/SpriteRenderer2D.h"

#include "ECS/ComponentManager.h"
#include <EclipsedEngine/DebugLogger.h>
#include "Core/Timer.h"

#include "EclipsedEngine/Components/Transform2D.h"

#include "Door.h"

#include "Core/EventSystem/EventSystem.h"

void EventBroadcaster::Broadcast(std::string evetnName)
{
	events.push_back(evetnName);
}
bool EventBroadcaster::Listen(std::string eventName)
{
	for (auto event : events)
	{
		if (event == eventName)
		{
			return true;
		}
	}

	return false;
}

void EventBroadcaster::Clear()
{
	events.clear();
}
