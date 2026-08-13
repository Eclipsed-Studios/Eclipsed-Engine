#pragma once

#include "OpenGL_Renderer.Core.hpp"
#include "EclipsedEngine/Graphics/IRenderer.h"

struct GLFWwindow;

namespace Eclipse::Graphics::OpenGL
{
	class OPENGL_RENDERER_API OpenGL_Renderer final : public IRenderer
	{
	public:
		ErrorCode Init() override;

		void BeginFrame() override;
		void EndFrame() override;

		bool ShouldWindowClose() override;

		void Render() override;

		void ImplImGui(void* imguiCtx) override;
	
		void ImGui_NewFrame() override;
		void ImGui_EndFrame() override;
	private:
		GLFWwindow* window;
	};
}