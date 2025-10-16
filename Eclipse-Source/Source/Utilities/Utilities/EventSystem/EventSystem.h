#pragma once

#include "Events/Event.h"
#include "Events/EventT.h"

namespace Eclipse
{
	class BaseEvent;
	class EventSystem
	{
	public:
		static void Subscribe(const char* eventName, BaseEvent* event);
		static void Unsubscribe(const char* eventName, int id);

		static void Invoke(const char* eventName);

		template <typename T>
		void Invoke(const char* eventName, T aVal)
		{
			EventRegistry& registry = GetRegistry();
			for (auto& [id, event] : registry[eventName])
			{
				EventT<T>* e = static_cast<EventT<T>*>(event);
				e->operator()(aVal);
			}
		}

	private:
		using EventRegistry = std::unordered_map<std::string, std::unordered_map<int, BaseEvent*>>;
		static EventRegistry& GetRegistry();

	private:
	};
}