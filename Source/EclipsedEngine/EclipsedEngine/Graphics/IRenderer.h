#pragma once

#include "EclipsedEngine/Input/AbstractInput.h"

class ErrorCode {};

namespace Eclipse::Graphics
{
	class IRenderer
	{
	public:
		virtual ErrorCode Init() { return ErrorCode{}; };

		virtual void BeginFrame() {};
		virtual void EndFrame() {};

		virtual bool ShouldWindowClose() { return true; };

		virtual void Render() {};

		virtual void ImGui_NewFrame() {};
		virtual void ImGui_Init(void* imguiCtx) {};
		virtual void ImGui_Render() {};

		virtual Input::AbstractInput* CreateInput() = 0;
	};
}