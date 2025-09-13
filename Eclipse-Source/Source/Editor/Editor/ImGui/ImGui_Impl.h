#pragma once

#define GLFW_EXPOSE_NATIVE_WIN32

#include "ImGui/ImGui/imgui.h"
#include "ImGui/ImGui/imgui_impl_glfw.h"
#include "ImGui/ImGui/imgui_impl_opengl3.h"

#include <string>

namespace Eclipse::Editor
{
    namespace ImGui_Impl
    {
        inline std::string currentEditorLayout = "Default";

        inline void ImplementImGui(GLFWwindow* aWindow)
        {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGui::StyleColorsDark();

            std::string path = ENGINE_ASSETS_PATH "Editor/Layouts/" + currentEditorLayout + ".ini";

            ImGuiIO& io = ImGui::GetIO();
            io.IniFilename = NULL;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
            io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

            ImGuiStyle& style = ImGui::GetStyle();
            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
                style.WindowRounding = 0.0f;
                style.Colors[ImGuiCol_WindowBg].w = 1.0f;
            }

            //io.FontDefault = io.Fonts->AddFontFromFileTTF(ENGINE_ASSETS_PATH "Fonts/Quicksand-Medium.ttf", 16);
            io.FontDefault = io.Fonts->AddFontFromFileTTF(ENGINE_ASSETS_PATH "Fonts/ARIAL.TTF", 16);

            ImGui_ImplGlfw_InitForOpenGL(aWindow, true);
            ImGui_ImplOpenGL3_Init("#version 460");

            ImGui::LoadIniSettingsFromDisk(path.c_str());
        }

        inline void NewFrame()
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();

            ImGui::NewFrame();

            ImGui::DockSpaceOverViewport(1, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
        }

        inline void Render()
        {
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        // Tools
        inline void DrawComponentHeader(const char* compName, bool& isDrawn, const float values = 0, ImGuiStyleVar styleFlags = ImGuiStyleVar_FrameRounding)
        {
            ImGui::PushStyleVar(styleFlags, values);
            isDrawn = ImGui::CollapsingHeader(compName);
            ImGui::PopStyleVar();
        }

    }
}