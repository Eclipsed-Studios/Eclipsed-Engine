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
	void SceneWindow::ZoomToObject()
	{
		if (!HierarchyWindow::CurrentGameObjectID)
			return;
		if (!InputMapper::ReadValue("ZoomToObject"))
			return;

		Transform2D* transform = ComponentManager::GetComponent<Transform2D>(HierarchyWindow::CurrentGameObjectID);

		myInspectorPosition = transform->GetPosition();
		myInspectorScale = Math::Vector2f(1, 1);
		totalYScroll = 0;
	}

	void SceneWindow::ScrollManager()
	{
		ImGuiIO& io = ImGui::GetIO();
		float deltaYScroll = io.MouseWheel;

		if (deltaYScroll == 0.0f)
			return;

		float zoomFactor = (deltaYScroll > 0) ? 1.05f : 0.95f;

		Math::Vector2f zoomCenter = normalizedMousePosition;

		myInspectorPosition = zoomCenter + (myInspectorPosition - zoomCenter) * (1.0f / zoomFactor);

		myInspectorScale *= {zoomFactor, zoomFactor};
	}

	void SceneWindow::MouseManager()
	{
		{
			ImVec2 mousePos = ImGui::GetMousePos();
			ImVec2 cursorScreenPos = ImGui::GetCursorScreenPos();
			ImVec2 windowSize = ImGui::GetWindowSize();

			windowRelativeMousePosition = { static_cast<unsigned>((mousePos.x - cursorScreenPos.x)), static_cast<unsigned>(windowSize.y - (mousePos.y - cursorScreenPos.y)) };

			normalizedMousePosition.x = windowRelativeMousePosition.x / windowSize.x;
			normalizedMousePosition.y = windowRelativeMousePosition.y / windowSize.y;

			normalizedMousePosition.x = normalizedMousePosition.x * 2.f - 1;
			normalizedMousePosition.y = normalizedMousePosition.y * 2.f - 1;
		}

		if (ImGui::IsWindowHovered())
		{
			if (ImGui::IsMouseDown(1) || ImGui::IsMouseDown(2))
				mouseIsDown = true;

			ScrollManager();
		}

		ImVec2 windowSize = ImGui::GetWindowSize();

		if (mouseIsDown)
		{
			ImGuiIO& io = ImGui::GetIO();
			ImVec2 mouseDelta = io.MouseDelta;

			float correctScaledWindowSizeY = windowSize.y;
			float SizeXRatio = windowSize.x * (windowSize.y / windowSize.x);

			Math::Vector2f mouseDragdelta = { mouseDelta.x, mouseDelta.y };
			myInspectorPosition -= Math::Vector2f(mouseDragdelta.x / SizeXRatio, -mouseDragdelta.y / correctScaledWindowSizeY) * 2.f * (1.f / myInspectorScale);

			GraphicsEngine::SetCursor(GraphicsEngine::MouseCursor::Grab);
		}

		if (!(ImGui::IsMouseDown(1) || ImGui::IsMouseDown(2)))
			mouseIsDown = false;






		if (!draggingSprite)
			return;

		ImGuiIO& io = ImGui::GetIO();
		ImVec2 mouseDelta = io.MouseDelta;
		Math::Vector2f mouseDeltaECL = Math::Vector2f((mouseDelta.x / windowSize.x) * (windowSize.x / windowSize.y), (mouseDelta.y / windowSize.y) * -1.f) * (1.f / myInspectorScale) * 2.f;

		int currentGO = HierarchyWindow::CurrentGameObjectID;
		Transform2D* transform = ComponentManager::GetComponent<Transform2D>(currentGO);
		transform->SetPosition(transform->GetPosition() + mouseDeltaECL);

		if (ImGui::IsMouseReleased(0))
			draggingSprite = false;
	}

	void SceneWindow::PixelPickCheck()
	{
		if (!ImGui::IsMouseClicked(0))
			return;
		if (!ImGui::IsWindowHovered())
			return;

		GraphicsEngine::ClearCurrentSceneBuffer(0, 0, 0);

		int ovColor = 0;
		GraphicsEngine::UpdateGlobalUniform(UniformType::Int, "notOverrideColor", &ovColor);

		CommandList::Execute();

		ImVec2 windowSize = ImGui::GetWindowSize();
		Math::Vector4ui colorValue = GraphicsEngine::ReadPixel({ windowRelativeMousePosition.x, windowRelativeMousePosition.y });
		int pickedID = colorValue.x + colorValue.y * 256 + colorValue.z * 256 * 256;

		HierarchyWindow::CurrentGameObjectID = pickedID;
		InspectorWindow::activeType = ActiveItemTypes_GameObject;

		if (!pickedID)
			return;

		draggingSprite = true;
	}


	void SceneWindow::Update()
	{
		if (ImGui::BeginMenuBar())
		{
			DrawGizmoButtons(DrawGizmo);

			ImGui::EndMenuBar();
		}

		MouseManager();
		ZoomToObject();

		GraphicsEngine::BindFrameBuffer(mySceneFrameBuffer);

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

		// This is not using its own framebuffer but if left click then render and get mouse position color
		PixelPickCheck();

		int notOvColor = 1;
		GraphicsEngine::UpdateGlobalUniform(UniformType::Int, "notOverrideColor", &notOvColor);

		GraphicsEngine::ClearCurrentSceneBuffer();

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

		ImGui::Image(mySceneTexture, ImVec2(windowSize.x, windowSize.y), ImVec2(0, 1), ImVec2(1, 0));

		GraphicsEngine::BindFrameBuffer(0);
	}

	void SceneWindow::InitSceneBuffers()
	{
		glGenFramebuffers(1, &mySceneFrameBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, mySceneFrameBuffer);

		glGenTextures(1, &mySceneTexture);
		glBindTexture(GL_TEXTURE_2D, mySceneTexture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1920, 1080, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, mySceneTexture, 0);
	}

	void SceneWindow::Open()
	{
		flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoScrollWithMouse;

		InitSceneBuffers();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}