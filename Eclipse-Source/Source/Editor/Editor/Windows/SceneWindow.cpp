#ifdef _EDITOR
#include "SceneWindow.h"

#include "ImGui/imgui.h"
#include "PhysicsEngine.h"
#include "PhysicsEngineSettings.h"

#include "Math/Math.h"

#include "OpenGL/OpenGLGraphicsAPI.h"

#include "RenderCommands/CommandList.h"

#include "Input/Input.h"

#include "RenderCommands/RenderCommand.h"

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

		float baseFactor = 1.07f;

		float scaleMagnitude = std::log2(myInspectorScale.x + 1.0f);
		float dynamicFactor = baseFactor - (0.02f * scaleMagnitude);

		dynamicFactor = std::max(1.001f, dynamicFactor);
		float zoomFactor = (deltaYScroll > 0) ? dynamicFactor : 1.0f / dynamicFactor;

		Math::Vector2f zoomCenter = normalizedMousePosition + myInspectorPosition;

		myInspectorPosition = zoomCenter + (myInspectorPosition - zoomCenter) * (1.0f / zoomFactor);

		myInspectorScale *= { zoomFactor, zoomFactor };
	}


	void SceneWindow::MouseManager()
	{
		{
			ImVec2 mousePos = ImGui::GetMousePos();
			ImVec2 cursorScreenPos = ImGui::GetCursorScreenPos();

			windowRelativeMousePosition = { static_cast<unsigned>((mousePos.x - cursorScreenPos.x)), static_cast<unsigned>(myWindowSize.y - (mousePos.y - cursorScreenPos.y)) };

			normalizedMousePosition.x = windowRelativeMousePosition.x / myWindowSize.x;
			normalizedMousePosition.y = windowRelativeMousePosition.y / myWindowSize.y;

			normalizedMousePosition.x = normalizedMousePosition.x * 2.f - 1;
			normalizedMousePosition.y = normalizedMousePosition.y * 2.f - 1;
		}

		if (ImGui::IsWindowHovered())
		{
			if (ImGui::IsMouseDown(1) || ImGui::IsMouseDown(2))
				mouseIsDown = true;

			ScrollManager();
		}

		if (mouseIsDown)
		{
			ImGuiIO& io = ImGui::GetIO();
			ImVec2 mouseDelta = io.MouseDelta;

			float correctScaledWindowSizeY = myWindowSize.y;
			float SizeXRatio = myWindowSize.x * (myWindowSize.y / myWindowSize.x);

			Math::Vector2f mouseDragdelta = { mouseDelta.x, mouseDelta.y };
			myInspectorPosition -= Math::Vector2f(mouseDragdelta.x / SizeXRatio, -mouseDragdelta.y / correctScaledWindowSizeY) * 2.f * (1.f / myInspectorScale);

			GraphicsEngine::SetCursor(GraphicsEngine::MouseCursor::Grab);
		}

		if (!(ImGui::IsMouseDown(1) || ImGui::IsMouseDown(2)))
			mouseIsDown = false;

		SpriteDragging();
	}

	void SceneWindow::SpriteDragging()
	{
		if (!draggingSprite)
			return;

		ImGuiIO& io = ImGui::GetIO();
		ImVec2 mouseDelta = io.MouseDelta;
		Math::Vector2f mouseDeltaECL = Math::Vector2f((mouseDelta.x / myWindowSize.x) * (myWindowSize.x / myWindowSize.y), (mouseDelta.y / myWindowSize.y) * -1.f) * (1.f / myInspectorScale) * 2.f;

		int currentGO = HierarchyWindow::CurrentGameObjectID;
		Transform2D* transform = ComponentManager::GetComponent<Transform2D>(currentGO);
		transform->SetPosition(transform->GetPosition() + mouseDeltaECL);

		if (ImGui::IsMouseReleased(0))
			draggingSprite = false;
	}

	void SceneWindow::SpriteSelecter()
	{
		if (!ImGui::IsMouseClicked(0))
			return;
		if (!ImGui::IsWindowHovered())
			return;

		GraphicsEngine::ClearCurrentSceneBuffer(0, 0, 0);

		int ovColor = 0;
		GraphicsEngine::UpdateGlobalUniform(UniformType::Int, "notOverrideColor", &ovColor);

		CommandList::Execute();

		Math::Vector4ui colorValue = GraphicsEngine::ReadPixel({ windowRelativeMousePosition.x + 10, windowRelativeMousePosition.y - 8 });
		int pickedID = colorValue.x + colorValue.y * 256 + colorValue.z * 256 * 256;

		if (ImGui::IsMouseClicked(0) && HierarchyWindow::CurrentGameObjectID == pickedID && HierarchyWindow::CurrentGameObjectID)
			draggingSprite = true;

		HierarchyWindow::CurrentGameObjectID = pickedID;
		InspectorWindow::activeType = ActiveItemTypes_GameObject;
	}


	void SceneWindow::Update()
	{
		ImVec2 windowSize = ImGui::GetWindowSize();
		myWindowSize = { windowSize.x, windowSize.y };

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

		glViewport(0, 0, myWindowSize.x, myWindowSize.y);

		float aspectRatio = myWindowSize.y / myWindowSize.x;
		GraphicsEngine::UpdateGlobalUniform(UniformType::Float, "resolutionRatio", &aspectRatio);

		// This is not using its own framebuffer but if left click then render and get mouse position color
		SpriteSelecter();

		int notOvColor = 1;
		GraphicsEngine::UpdateGlobalUniform(UniformType::Int, "notOverrideColor", &notOvColor);

		GraphicsEngine::ClearCurrentSceneBuffer();


		if (HierarchyWindow::CurrentGameObjectID)
		{
			mySelectedObject = GetComp(SpriteRenderer2D, HierarchyWindow::CurrentGameObjectID);

			if (mySelectedObject)
			{
				Transform2D* transform = GetComp(Transform2D, HierarchyWindow::CurrentGameObjectID);

				DebugDrawer::Get().Begin();
				Math::Vector2f textureScale = mySelectedObject->GetMaterial()->myTexture->GetTextureSizeNormilized();
				Math::Vector2f size = mySelectedObject->spriteRectMax - mySelectedObject->spriteRectMin;
				float aspectScale = size.y / size.x;

				DebugDrawer::DrawSquare(transform->GetPosition() * 0.5f + Math::Vector2f(0.5f, 0.5f), transform->GetScale() * 0.01f * 0.5f * textureScale * Math::Vector2f(1.f, aspectScale), Math::Color(1.f, 0.4f, 0.7f, 1.f));
				DebugDrawer::Get().Render();
			}
		}

		CommandList::Execute();

		// if (mySelectedObject)
		// {
		// 	mySelectedObject->Draw(mySelectedSpriteHighlightProgram);
		// }


		GraphicsEngine::UpdateGlobalUniform(UniformType::Vector2f, "cameraPosition", &lastInspectorPosition);
		GraphicsEngine::UpdateGlobalUniform(UniformType::Float, "cameraRotation", &lastInspectorRotation);
		GraphicsEngine::UpdateGlobalUniform(UniformType::Vector2f, "cameraScale", &lastInspectorScale);

		if (myWindowSize.x != myLastWindowResolution.x || myWindowSize.y != myLastWindowResolution.y)
		{
			glBindTexture(GL_TEXTURE_2D, mySceneTexture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, myWindowSize.x, myWindowSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		myLastWindowResolution = { myWindowSize.x, myWindowSize.y };

		ImVec2 CursorPos = ImGui::GetCursorPos();
		ImGui::SetCursorPos(ImVec2(CursorPos.x - 8, CursorPos.y - 7));
		ImGui::Image(mySceneTexture, ImVec2(myWindowSize.x, myWindowSize.y), ImVec2(0, 1), ImVec2(1, 0));

		GraphicsEngine::BindFrameBuffer(0);
	}

	void SceneWindow::InitSceneBuffer()
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

	void SceneWindow::InitSelectedObjectShader()
	{
		unsigned vertexShaderID = 0;
		unsigned pixelShaderID = 0;

		ResourcePointer<VertexShader> myVertexShader = Resources::Get<VertexShader>(ASSET_PATH"Shaders/SelectedVertexSpriteShader.glsl");
		ResourcePointer<PixelShader> myPixelShader = Resources::Get<PixelShader>(ASSET_PATH"Shaders/SelectedPixelSpriteShader.glsl");

		mySelectedSpriteHighlightProgram = glCreateProgram();
		glAttachShader(mySelectedSpriteHighlightProgram, myVertexShader->GetVertexShaderID());
		glAttachShader(mySelectedSpriteHighlightProgram, myPixelShader->GetPixelShaderID());
		glLinkProgram(mySelectedSpriteHighlightProgram);
	}

	void SceneWindow::Open()
	{
		flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoScrollWithMouse;

		InitSceneBuffer();
		InitSelectedObjectShader();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
#endif