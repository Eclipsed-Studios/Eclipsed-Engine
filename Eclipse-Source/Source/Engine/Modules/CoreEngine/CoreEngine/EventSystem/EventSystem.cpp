#include "pch.h"

#include "EventSystem.h"

#include "Events/Event.h"

namespace Eclipse
{
	void EventSystem::Subscribe(const char* eventName, BaseEvent* event)
	{
		EventRegistry& registry = GetRegistry();
		registry[eventName].emplace(event->GetID(), event);
	}

	void EventSystem::Unsubscribe(const char* eventName, int id)
	{
		EventRegistry& registry = GetRegistry();

		if (registry.find(eventName) != registry.end())
		{
			if (registry[eventName].find(id) != registry[eventName].end())
			{
				registry[eventName].erase(id);
			}
		}
	}

	void EventSystem::Invoke(const char* eventName)
	{
		EventRegistry& registry = GetRegistry();
		for (auto& [id, event] : registry[eventName])
		{
			Event* e = static_cast<Event*>(event);
			e->operator()();
		}
	}

	EventSystem::EventRegistry& EventSystem::GetRegistry()
	{
		static EventSystem::EventRegistry registry;
		return registry;
	}
}