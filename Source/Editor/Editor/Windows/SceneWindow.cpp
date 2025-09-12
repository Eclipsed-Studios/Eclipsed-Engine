#include "SceneWindow.h"

#include "ImGui/imgui.h"
#include "PhysicsEngine.h"
#include "PhysicsEngineSettings.h"

#include "Math/Math.h"

#include "OpenGL/OpenGLGraphicsAPI.h"

#include "CommandList.h"

namespace Eclipse::Editor
{
	void SceneWindow::Update()
	{
		if (ImGui::BeginMenuBar())
		{
			DrawGizmoButtons(DrawGizmo);

			ImGui::EndMenuBar();
		}

		// These clear colors are not working like they should and get mixed up so the first is the empty background and second is the actual
		GraphicsEngine::BindFrameBuffer(mySceneFrameBuffer);
		GraphicsEngine::ClearCurrentSceneBuffer(0.3f, 0.3f, 0.3f);

		Math::Vector2f lastInspectorPosition(0, 0);
		float lastInspectorRotation = 0;
		Math::Vector2f lastInspectorScale(1, 1);

		Math::Vector2f inspectorPosition(0, 0);
		float inspectorRotation = 0;
		Math::Vector2f inspectorScale(1, 1);

		GraphicsEngine::GetGlobalUniform(UniformType::Vector2f, "cameraPosition", &lastInspectorPosition);
		GraphicsEngine::GetGlobalUniform(UniformType::Float, "cameraRotation", &lastInspectorRotation);
		GraphicsEngine::GetGlobalUniform(UniformType::Vector2f, "cameraScale", &lastInspectorScale);

		GraphicsEngine::UpdateGlobalUniform(UniformType::Vector2f, "cameraPosition", &inspectorPosition);
		GraphicsEngine::UpdateGlobalUniform(UniformType::Float, "cameraRotation", &inspectorRotation);
		GraphicsEngine::UpdateGlobalUniform(UniformType::Vector2f, "cameraScale", &inspectorScale);

		ImVec2 windowSize = ImGui::GetWindowSize();

        float aspectRatio = windowSize.y / windowSize.x;
        GraphicsEngine::UpdateGlobalUniform(UniformType::Float, "resolutionRatio", &aspectRatio);

		CommandList::Execute();

		GraphicsEngine::UpdateGlobalUniform(UniformType::Vector2f, "cameraPosition", &lastInspectorPosition);
		GraphicsEngine::UpdateGlobalUniform(UniformType::Float, "cameraRotation", &lastInspectorRotation);
		GraphicsEngine::UpdateGlobalUniform(UniformType::Vector2f, "cameraScale", &lastInspectorScale);

		if (windowSize.x != myLastWindowResolution.x || windowSize.y != myLastWindowResolution.y)
		{
			glBindTexture(GL_TEXTURE_2D, mySceneTexture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, windowSize.x, windowSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		myLastWindowResolution = { static_cast<int>(windowSize.x), static_cast<int>(windowSize.y) };

		ImGui::SetCursorPos(ImVec2(0, 0));
		ImGui::Image(mySceneTexture, windowSize, ImVec2(0, 1), ImVec2(1, 0));

		GraphicsEngine::BindFrameBuffer(0);
		GraphicsEngine::ClearCurrentSceneBuffer();
	}

	void SceneWindow::Open()
	{
		flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoScrollWithMouse;

		glGenTextures(1, &mySceneTexture);
		glGenFramebuffers(1, &mySceneFrameBuffer);

		GraphicsEngine::BindFrameBuffer(mySceneFrameBuffer);

		glBindTexture(GL_TEXTURE_2D, mySceneTexture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1920, 1080, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, mySceneTexture, 0);

		GraphicsEngine::BindFrameBuffer(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}