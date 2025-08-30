#pragma once

#define GLFW_EXPOSE_NATIVE_WIN32

#include "ImGui/ImGui/imgui.h"
#include "ImGui/ImGui/imgui_impl_glfw.h"
#include "ImGui/ImGui/imgui_impl_opengl3.h"

namespace ENGINE_NAMESPACE::EditorContext
{
	namespace ImGui_Impl
	{
		inline void ImplementImGui(GLFWwindow* aWindow)
        {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGui::StyleColorsDark();

            ImGuiIO& io = ImGui::GetIO();
            io.IniFilename = NULL;

            //ImGui::LoadIniSettingsFromDisk(IMGUISETTINGSDIR);

            // Setup Platform/Renderer bindings
            ImGui_ImplGlfw_InitForOpenGL(aWindow, true);
            ImGui_ImplOpenGL3_Init("#version 460");
        }
	}
}