#include "Profiler.h"

namespace Eclipse::Profiler
{
	void ProfilerManager::BeginAndClearDataCollection()
	{
		shouldCollectData = true;

		startTimes.clear();
		records.clear();
	}

	void ProfilerManager::EndDataCollection()
	{
		shouldCollectData = false;
	}

	void ProfilerManager::BeginProfile(const std::string& name)
	{
		if (!shouldCollectData) return;
		startTimes[name] = std::chrono::high_resolution_clock::now();
	}

	void ProfilerManager::EndProfile(const std::string& name)
	{
		if (!shouldCollectData) return;
		std::chrono::high_resolution_clock::time_point& start = startTimes[name];
		std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

		float duration = std::chrono::duration<float, std::milli>(end - start).count();

		ProfileRecord record;
		record.calls++;
		record.totalTime += duration;

		if (duration > record.highestTime) record.highestTime = duration;
		if (duration < record.lowestTime) record.lowestTime = duration;

		records[name].Push(record);

		startTimes.erase(name);
	}
	
	bool ProfilerManager::IsStarted()
	{
		return shouldCollectData;
	}

	const std::unordered_map<std::string, Utilities::RingBuffer<ProfileRecord, MAX_PROFILER_RECORDS>> ProfilerManager::GetRecords()
	{
		return records;
	}
}