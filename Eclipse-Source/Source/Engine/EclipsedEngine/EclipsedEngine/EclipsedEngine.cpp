#include "EclipsedEngine.h"

namespace Eclipse
{
	void EclipsedEngine::Update()
	{
		Internal_BeginFrame();
		Internal_Update();
		Internal_EndFrame();
	}


	void EclipsedEngine::Internal_Update()
	{

	}

	void EclipsedEngine::Internal_EndFrame()
	{
	}

	void EclipsedEngine::Internal_BeginFrame()
	{
	}
}
