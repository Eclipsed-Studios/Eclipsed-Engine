#include "BaseEvent.h"

#include "EventSystem/EventSystem.h"

namespace Eclipse
{
	BaseEvent::BaseEvent(const char* anEventName)
	{
		eventName = anEventName;

		id = Random::GetValue<int>();
		EventSystem::Subscribe(eventName.c_str(), this);
	}

	BaseEvent::~BaseEvent()
	{
		EventSystem::Unsubscribe(eventName.c_str(), id);
	}
}
