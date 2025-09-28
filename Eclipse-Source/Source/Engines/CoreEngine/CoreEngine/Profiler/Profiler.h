#pragma once

#include "RingBuffer.h"

#define MAX_PROFILER_RECORDS 2000


namespace Eclipse::Profiler
{
	struct ProfileRecord {
		int calls = 0;
		float totalTime = 0.f;
		float highestTime = FLT_MIN, lowestTime = FLT_MAX;
	};

	class ProfilerManager
	{
	public:
		static void BeginAndClearDataCollection();
		static void EndDataCollection();

		static void BeginProfile(const std::string& name);
		static void EndProfile(const std::string& name);

		static bool IsStarted();

		static const std::unordered_map<std::string, Utilities::RingBuffer<ProfileRecord, MAX_PROFILER_RECORDS>> GetRecords();

	private:
		static inline bool shouldCollectData = false;
		static inline std::unordered_map<std::string, std::chrono::high_resolution_clock::time_point> startTimes;
		static inline std::unordered_map<std::string, Utilities::RingBuffer<ProfileRecord, MAX_PROFILER_RECORDS>> records;
	};
}