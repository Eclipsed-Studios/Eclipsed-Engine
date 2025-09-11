#include "GameWindow.h"

#include "ImGui/imgui.h"
#include "PhysicsEngine.h"
#include "PhysicsEngineSettings.h"

#include "Math/Math.h"

#include "OpenGL/OpenGLGraphicsAPI.h"

#include "CommandList.h"

namespace Eclipse::Editor
{
    void GameWindow::Update()
    {
        // These clear colors are not working like they should and get mixed up so the first is the empty background and second is the actual
        GraphicsEngine::BindFrameBuffer(myGameFrameBuffer);
        GraphicsEngine::ClearCurrentSceneBuffer(0.3f, 0.3f, 0.3f);

        CommandList::Execute();

        ImVec2 windowSize = ImGui::GetWindowSize();

        if (windowSize.x != myLastWindowResolution.x || windowSize.y != myLastWindowResolution.y)
        {
            glBindTexture(GL_TEXTURE_2D, myGameTexture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, windowSize.x, windowSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        myLastWindowResolution = { static_cast<int>(windowSize.x), static_cast<int>(windowSize.y) };

        ImGui::SetCursorPos(ImVec2(0, 0));
        ImGui::Image(myGameTexture, windowSize, ImVec2(0, 1), ImVec2(1, 0));

        GraphicsEngine::BindFrameBuffer(0);
        GraphicsEngine::ClearCurrentSceneBuffer();
    }

    void GameWindow::Open()
    {
        flags |= ImGuiWindowFlags_NoScrollbar;



        glGenTextures(1, &myGameTexture);
        glGenFramebuffers(1, &myGameFrameBuffer);

        GraphicsEngine::BindFrameBuffer(myGameFrameBuffer);

        glBindTexture(GL_TEXTURE_2D, myGameTexture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1920, 1080, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, myGameTexture, 0);

        GraphicsEngine::BindFrameBuffer(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}