#include "DebugInformationCollector.h"

namespace Eclipse
{
	int DebugInformationCollector::GetRenderCalls()
	{
		return renderCalls;
	}

	void DebugInformationCollector::UpdateRenderCalls(int amount)
	{
		renderCalls += amount;
	}

	void DebugInformationCollector::ResetRenderCalls()
	{
		renderCalls = 0;
	}
}