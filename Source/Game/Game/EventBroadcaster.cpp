#include "EventBroadcaster.h"

#include "EclipsedEngine/Components/Rendering/SpriteRenderer2D.h"

#include "ECS/ComponentManager.h"
#include <EclipsedEngine/DebugLogger.h>
#include "Core/Timer.h"

#include "EclipsedEngine/Components/Transform2D.h"

#include "Door.h"

#include "Core/EventSystem/EventSystem.h"

void EventBroadcaster::Broadcast(const std::string& evetnName)
{
	events.push_back(evetnName);
}
bool EventBroadcaster::Listen(const std::string& eventName)
{
	for (auto& event : events)
	{
		if (event == eventName)
		{
			return true;
		}
	}

	return false;
}

void EventBroadcaster::DeleteEvent(const std::string& eventName)
{
	for (int i = 0; i < events.size(); i++)
	{
		auto& event = events[i];

		if (event == eventName)
		{
			events.back() = events[i];
			events.pop_back();
		}
	}
}

void EventBroadcaster::Clear()
{
	events.clear();
}
