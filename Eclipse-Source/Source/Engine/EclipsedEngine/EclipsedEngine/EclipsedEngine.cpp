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

	}

	void EclipsedEngine::Internal_EndFrame()
	{
	}

	void EclipsedEngine::Internal_BeginFrame()
	{
	}
}
