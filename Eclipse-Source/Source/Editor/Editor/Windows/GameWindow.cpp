#include "GameWindow.h"

#include "ImGui/imgui.h"
#include "PhysicsEngine.h"
#include "PhysicsEngineSettings.h"

#include "Math/Math.h"

#include "OpenGL/OpenGLGraphicsAPI.h"

#include "RenderCommands/CommandList.h"

#include <array>

namespace Eclipse::Editor
{
    std::array<std::string, 2> resolutionChooser{ "Free Aspect", "16:9" };

    void GameWindow::Update()
    {
        if (ImGui::BeginMenuBar())
        {
            std::stringstream ss;
            ss << "Resolution: " << myCurrentWindowRes;

            if (ImGui::Button(ss.str().c_str()))
                ImGui::OpenPopup("Res");

            if (ImGui::BeginPopup("Res"))
            {
                for (auto& res : resolutionChooser)
                {
                    if (ImGui::Selectable(res.c_str()))
                    {
                        myCurrentWindowRes = res;
                    }
                }

                ImGui::EndPopup();
            }


            DrawGizmoButtons(DrawGizmo);

            ImGui::EndMenuBar();
        }

        ImVec2 windowSize = ImGui::GetWindowSize();
        if (!Camera::main)
        {
            ImVec2 size = ImGui::CalcTextSize("No Camera Rendering");
            ImGui::SetCursorPos({ windowSize.x * 0.5f - size.x * 0.5f, windowSize.y * 0.5f - size.y * 0.5f + 43 * 0.5f });
            ImGui::Text("No Camera Rendering");
            return;
        }


        // These clear colors are not working like they should and get mixed up so the first is the empty background and second is the actual
        GraphicsEngine::BindFrameBuffer(myGameFrameBuffer);
        GraphicsEngine::ClearCurrentSceneBuffer();


        TemporarySettingsSingleton::Get().resolutionRatioGameView = windowSize.x / windowSize.y;


        // if (myCurrentWindowRes == "16:9")
        // {
            //     windowSize.x = windowSize.y * 1.777777f;
            // }


        glViewport(0, 0, windowSize.x, windowSize.y);

        float aspectRatio = windowSize.y / windowSize.x;
        GraphicsEngine::UpdateGlobalUniform(UniformType::Float, "resolutionRatio", &aspectRatio);

        CommandList::Execute();

        if (windowSize.x != myLastWindowResolution.x || windowSize.y != myLastWindowResolution.y)
        {
            glBindTexture(GL_TEXTURE_2D, myGameTexture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, windowSize.x, windowSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
            glBindTexture(GL_TEXTURE_2D, 0);

            // Also update the framebuffer attachment
            glBindFramebuffer(GL_FRAMEBUFFER, myGameFrameBuffer);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, myGameTexture, 0);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        myLastWindowResolution = { static_cast<int>(windowSize.x), static_cast<int>(windowSize.y) };

        ImGui::SetCursorPos(ImVec2(0, 43));
        ImGui::Image(myGameTexture, ImVec2(windowSize.x, windowSize.y - 64), ImVec2(0, 1), ImVec2(1, 0));

        GraphicsEngine::BindFrameBuffer(0);
    }

    void GameWindow::Open()
    {
        myCurrentWindowRes = resolutionChooser[0];

        flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoScrollWithMouse;



        glGenTextures(1, &myGameTexture);
        glGenFramebuffers(1, &myGameFrameBuffer);

        GraphicsEngine::BindFrameBuffer(myGameFrameBuffer);

        glBindTexture(GL_TEXTURE_2D, myGameTexture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1920, 1080, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, myGameTexture, 0);

        GraphicsEngine::BindFrameBuffer(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}