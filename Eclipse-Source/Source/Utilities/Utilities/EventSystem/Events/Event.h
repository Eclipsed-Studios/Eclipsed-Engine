#pragma once

#include <type_traits>
#include "BaseEvent.h"

namespace Eclipse
{
	class Event : public BaseEvent
	{
		struct EventCallback
		{
			void* fnPtr = nullptr;
			std::function<void()> fn;
		};

	public:
		using BaseEvent::BaseEvent;

	public:
		template<typename F>
		void operator+=(F&& aCallback)
		{
			EventCallback callback;
			callback.fn = aCallback;

			if constexpr(std::is_pointer_v<std::decay_t<F>>)
				callback.fnPtr = reinterpret_cast<void*>(aCallback);

			callbacks.push_back(callback);
		}

		template<typename F>
		void operator-=(F&& aCallback)
		{
			void* fnPtr = nullptr;
			if constexpr (std::is_pointer_v<std::decay_t<F>>)
				fnPtr = reinterpret_cast<void*>(aCallback);
			else return;

			callbacks.erase(
				std::remove_if(callbacks.begin(), callbacks.end(),
					[fnPtr](const EventCallback& callback) { return callback.fnPtr == fnPtr;}),
				callbacks.end()
			);
		}

		void operator()()
		{
			for (EventCallback& callback : callbacks)
			{
				callback.fn();
			}
		}

	private:
		std::vector<EventCallback> callbacks;
	};
}
