#pragma once

#include "CoreEngine/Profiling/PerformanceProfilerManager.h"
#include "CoreEngine/Profiling/ProfilerNode.h"
#include "CoreEngine/Macros/defines.h"




class ECLIPSED_API Profiler
{
public:
	static void StartProfilingNode(ProfilerNode* aNode) { PerformanceProfilerManager::StartProfilingNode(aNode); }
	static void EndProfilingNode() { PerformanceProfilerManager::EndProfilingNode(); }

	static void Clear() { PerformanceProfilerManager::Clear(); }

	static void Print() { PerformanceProfilerManager::Print(); }

	static void CollectNextFrame() { PerformanceProfilerManager::CollectNextFrame(); }

	static ProfilerNode* GetCurrentNode() { return PerformanceProfilerManager::GetCurrentNode(); }
};


struct ScopedProfilerNodeRegistrator
{
	ScopedProfilerNodeRegistrator(const char* aName, const char* aFile, int aLine)
	{
		ProfilerNode* node = new ProfilerNode(aName, aFile, aLine);
		Profiler::StartProfilingNode(node);
	}
	~ScopedProfilerNodeRegistrator()
	{
		Profiler::EndProfilingNode();
	}
};

struct ProfilerNodeRegistrator
{
	ProfilerNodeRegistrator(const char* aName, const char* aFile, int aLine)
	{
		{
			ProfilerNode* node = new ProfilerNode(aName, aFile, aLine);
			Profiler::StartProfilingNode(node);
		}
	}
};

#define PROFILE_SCOPED ScopedProfilerNodeRegistrator GET_NAME(registrator_)(__FUNCTION__, __FILE__, __LINE__);
