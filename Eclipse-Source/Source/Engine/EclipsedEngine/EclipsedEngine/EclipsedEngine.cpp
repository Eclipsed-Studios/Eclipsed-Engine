#include "EclipsedEngine.h"

#include "Utilities/Common/MainSingleton.h"
#include "InputEngine/Input.h"


namespace Eclipse
{
	void EclipsedEngine::StartEngine()
	{
	}


	void EclipsedEngine::Update()
	{
		Internal_BeginFrame();
		Internal_Update();
		Internal_EndFrame();
	}


	void EclipsedEngine::Internal_Update()
	{
		int i = 0;
		while (i < 10) i++;
	}

	void EclipsedEngine::Internal_EndFrame()
	{
	}

	void EclipsedEngine::Internal_BeginFrame()
	{
	}
}
