#include "OpenGL_Renderer.h"

#include "OpenGL/glad/glad.h"
#include "OpenGL/GLFW/glfw3.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include "OpenGL/ImGui/imgui_impl_glfw.h"
#include "OpenGL/ImGui/imgui_impl_opengl3.h"

#include "EclipsedEngine/MainSingleton.h"

namespace Eclipse::Graphics::OpenGL
{
	ErrorCode OpenGL_Renderer::Init()
	{
		if (!glfwInit())
		{
			return ErrorCode{};
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

		float width = 1280;
		float height = 720;

		window = glfwCreateWindow(width, height, "Eclipsed Game Engine", nullptr, nullptr);

		glfwMakeContextCurrent(window);

		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		return ErrorCode{};
	}

	void OpenGL_Renderer::BeginFrame()
	{
		glClearColor(0.3f, 0.3f, 0.3f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGL_Renderer::EndFrame()
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	bool OpenGL_Renderer::ShouldWindowClose()
	{
		return glfwWindowShouldClose(window);
	}

	void OpenGL_Renderer::Render()
	{
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void OpenGL_Renderer::ImplImGui(void* imguiCtx)
	{
		ImGui::SetCurrentContext((ImGuiContext*)imguiCtx);

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 460");
	}

	void OpenGL_Renderer::ImGui_NewFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
	}

	void OpenGL_Renderer::ImGui_EndFrame()
	{

	}
}