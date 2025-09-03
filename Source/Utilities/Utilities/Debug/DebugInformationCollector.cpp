#include "DebugInformationCollector.h"

namespace ENGINE_NAMESPACE
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