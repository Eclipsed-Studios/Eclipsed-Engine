#pragma once

namespace Eclipse
{
	class BaseEvent
	{
	public:
		BaseEvent(const char* anEventName);
		BaseEvent() = default;

		~BaseEvent();

		int GetID() { return id; }
		const std::string& GetName() { return eventName; }

	private:
		int id = 0;
		std::string eventName = "";
	};
}
