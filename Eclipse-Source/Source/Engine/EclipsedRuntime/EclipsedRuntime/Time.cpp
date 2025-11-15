#include "Time.h"

#include "Utilities/Common/Timer.h"

static Time l_time;

float Time::GetDeltaTime()
{
	return Eclipse::Time::GetDeltaTime();
}
float Time::GetTotalTime()
{
	return Eclipse::Time::GetTotalTime();
}


ECL_RUNTIME_API Time& GetTimer()
{
	return l_time;
}
