#ifndef PROFILER_MACROS_H
#define PROFILER_MACROS_H


#ifdef ECLIPSED_EDITOR

#include "Profiler.h"

#define BEGIN_PROFILE_SCOPE(Name) Profiler::ProfilerManager::BeginProfile(Name)
#define END_PROFILE_SCOPE(Name) Profiler::ProfilerManager::EndProfile(Name)

#else

#define BEGIN_PROFILE_SCOPE(Name)
#define END_PROFILE_SCOPE(Name)

#endif


#endif