#pragma once

#include <vector>
#include <unordered_map>
#include <functional>
#include <thread>

namespace Eclipse::Editor
{
	enum class EventType : unsigned
	{
		Modified = (1 << 0),
		FileAdded = (1 << 1),
		FileRemoved = (1 << 2),
		RenamedOld = (1 << 3),
		RenamedNew = (1 << 4),

		Any = ~0
	};

	class FileWatcher final
	{
	public:
		FileWatcher() = delete;
		~FileWatcher() = delete;

		static void Start();
		static void Stop();

		static void Subscribe(EventType type, std::function<void(const std::string&)> func);

		static void HandleEvent(EventType event, const std::string& path);

	private:
		static inline bool started = false;
		static inline std::thread filewatcherThread;
		static inline std::unordered_map<EventType, std::vector<std::function<void(const std::string&)>>> subscribedEvents;
	};
}