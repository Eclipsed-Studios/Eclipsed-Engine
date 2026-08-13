#pragma once

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
		virtual void ImGui_EndFrame() {};
		virtual void ImplImGui(void* imguiCtx) {};
	};
}