#include "SceneWindow.h"

#include "ImGui/imgui.h"
#include "PhysicsEngine.h"
#include "PhysicsEngineSettings.h"

#include "Math/Math.h"

#include "OpenGL/OpenGLGraphicsAPI.h"

#include "RenderCommands/CommandList.h"

#include "Input/Input.h"

#include <iostream>

namespace Eclipse::Editor
{
	void SceneWindow::MoveCamera()
	{
		ImGuiIO& io = ImGui::GetIO();
		float deltaYScroll = io.MouseWheel;

		if (ImGui::IsWindowHovered())
		{
			if (ImGui::IsMouseDown(1) || ImGui::IsMouseDown(2))
			{
				mouseIsDown = true;
			}

			totalYScroll += deltaYScroll * 0.05f;
			myInspectorScale = { totalYScroll + 1.f, totalYScroll + 1.f };

			if (deltaYScroll > 0)
			{
				ImGui::SetCursorPos(ImVec2(0, 0));

				ImVec2 mousePos = ImGui::GetMousePos();
				ImVec2 cursorScreenPos = ImGui::GetCursorScreenPos();
				ImVec2 windowSize = ImGui::GetWindowSize();


				Math::Vector2f relativeMousePosEcl;

				relativeMousePosEcl.x = (mousePos.x - cursorScreenPos.x) / windowSize.x;
				relativeMousePosEcl.y = 1 - (mousePos.y - cursorScreenPos.y) / windowSize.y;

				relativeMousePosEcl.x = relativeMousePosEcl.x * 2.f - 1;
				relativeMousePosEcl.y = relativeMousePosEcl.y * 2.f - 1;

				myInspectorPosition += relativeMousePosEcl * 0.1f;
			}

		}
		if (mouseIsDown)
		{
			ImVec2 windowSize = ImGui::GetWindowSize();
			ImGuiIO& io = ImGui::GetIO();
			ImVec2 mouseDelta = io.MouseDelta;

			Math::Vector2i mouseDragdelta = { static_cast<int>(mouseDelta.x), static_cast<int>(mouseDelta.y) };
			myInspectorPosition -= Math::Vector2f(mouseDragdelta.x / (windowSize.x * (windowSize.y / windowSize.x)), -mouseDragdelta.y / windowSize.y) * 2.f * (1.f / myInspectorScale);

			GraphicsEngine::SetCursor(GraphicsEngine::MouseCursor::Grab);
		}

		if (!(ImGui::IsMouseDown(1) || ImGui::IsMouseDown(2)))
			mouseIsDown = false;
	}

	void SceneWindow::Update()
	{
		if (ImGui::BeginMenuBar())
		{
			DrawGizmoButtons(DrawGizmo);

			ImGui::EndMenuBar();
		}

		MoveCamera();

		// These clear colors are not working like they should and get mixed up so the first is the empty background and second is the actual
		GraphicsEngine::BindFrameBuffer(mySceneFrameBuffer);
		GraphicsEngine::ClearCurrentSceneBuffer();

		Math::Vector2f lastInspectorPosition(0, 0);
		float lastInspectorRotation = 0;
		Math::Vector2f lastInspectorScale(1, 1);

		GraphicsEngine::GetGlobalUniform(UniformType::Vector2f, "cameraPosition", &lastInspectorPosition);
		GraphicsEngine::GetGlobalUniform(UniformType::Float, "cameraRotation", &lastInspectorRotation);
		GraphicsEngine::GetGlobalUniform(UniformType::Vector2f, "cameraScale", &lastInspectorScale);

		GraphicsEngine::UpdateGlobalUniform(UniformType::Vector2f, "cameraPosition", &myInspectorPosition);
		GraphicsEngine::UpdateGlobalUniform(UniformType::Float, "cameraRotation", &myInspectorRotation);
		GraphicsEngine::UpdateGlobalUniform(UniformType::Vector2f, "cameraScale", &myInspectorScale);

		ImVec2 windowSize = ImGui::GetWindowSize();

		glViewport(0, 0, windowSize.x, windowSize.y);

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

		ImGui::SetCursorPos(ImVec2(0, 43));
		ImGui::Image(mySceneTexture, ImVec2(windowSize.x, windowSize.y - 43), ImVec2(0, 1), ImVec2(1, 0));

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