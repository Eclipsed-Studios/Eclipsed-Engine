#ifdef ECLIPSED_EDITOR
#include "SceneWindow.h"

#include "ImGui/imgui.h"

#include "Utilities/Math/Math.h"

#include "GraphicsEngine/OpenGL/OpenGLGraphicsAPI.h"
#include "GraphicsEngine/RenderCommands/CommandList.h"

#include "CoreEngine/Input/Input.h"

#include "GraphicsEngine/RenderCommands/RenderCommand.h"

#include <iostream>

#include "Utilities/Reflection/Registry/ComponentRegistry.h"

#include "CoreEngine/Components/Base/Component.h"
#include "CoreEngine/Components/Rendering/SpriteRenderer2D.h"
#include "CoreEngine/Components/UI/Canvas.h"

#include "CoreEngine/Input/InputMapper.h"
#include "CoreEngine/Components/Transform2D.h"

#include "GraphicsEngine/OpenGL/DebugDrawers/DebugDrawer.h"

#include "OpenGL/glad/glad.h"


namespace Eclipse
{
	using namespace Editor;

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

			// cursorScreenPos.x -= 8;
			// cursorScreenPos.y -= 8;

			float mousePosX = mousePos.x - cursorScreenPos.x;
			float mousePosY = myWindowSize.y - (mousePos.y - cursorScreenPos.y);

			windowRelativeMousePosition = { static_cast<unsigned>(mousePosX), static_cast<unsigned>(mousePosY) };

			normalizedMousePosition.x = windowRelativeMousePosition.x / myWindowSize.x;
			normalizedMousePosition.y = windowRelativeMousePosition.y / myWindowSize.y;

			normalizedMousePosition.x = normalizedMousePosition.x * 2.f - 1;
			normalizedMousePosition.y = normalizedMousePosition.y * 2.f - 1;

			if (ImGui::IsMouseClicked(0))
			{
				int i = 0;
			}

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

		mySpriteMoveVector += mouseDeltaECL;

		Math::Vector2f positionSnappPosition = mySpriteMoveVector;
		if (myIsSnapping)
		{
			float roundX = std::round(mySpriteMoveVector.x / mySnappingDistance) * mySnappingDistance;
			float roundY = std::round(mySpriteMoveVector.y / mySnappingDistance) * mySnappingDistance;
			positionSnappPosition = { roundX, roundY };
		}

		transform->SetPosition(mySpriteMouseDownPosition + positionSnappPosition);

		if (ImGui::IsMouseReleased(0))
			draggingSprite = false;
	}

	void SceneWindow::SpriteSelecter()
	{
		if (!ImGui::IsMouseClicked(0))
			return;
		if (!ImGui::IsWindowHovered())
			return;
		if (myGizmoMoveY || myGizmoMoveX)
			return;

		GraphicsEngine::ClearCurrentSceneBuffer(0, 0, 0);

		int ovColor = 0;
		GraphicsEngine::UpdateGlobalUniform(UniformType::Int, "notOverrideColor", &ovColor);

		CommandListManager::GetSpriteCommandList().Execute();

		Math::Vector4ui colorValue = GraphicsEngine::ReadPixel({ windowRelativeMousePosition.x + 10, windowRelativeMousePosition.y - 8 });
		int pickedID = colorValue.x + colorValue.y * 256 + colorValue.z * 256 * 256;

		if (HierarchyWindow::CurrentGameObjectID == pickedID && HierarchyWindow::CurrentGameObjectID)
		{
			if (ImGui::IsKeyDown(ImGuiKey_LeftAlt) || ImGui::IsKeyDown(ImGuiKey_RightAlt))
			{
				HierarchyWindow::Copy();
				HierarchyWindow::Paste();
			}

			Transform2D* transform = ComponentManager::GetComponent<Transform2D>(HierarchyWindow::CurrentGameObjectID);

			if (!transform)
				return;

			draggingSprite = true;

			mySpriteMouseDownPosition = transform->GetPosition();
			mySpriteMoveVector = { 0, 0 };
		}

		HierarchyWindow::CurrentGameObjectID = pickedID;
		InspectorWindow::activeType = ActiveItemTypes_GameObject;
	}


	void SceneWindow::ObjectSnappingGizmo()
	{
		ImGui::Checkbox("Snap##MoreSnappingIDSThatShouldBEUSED!!!ANDITISNOW:D", &myIsSnapping);

		if (myIsSnapping)
		{
			ImGui::Dummy({ 30, 0 });
			ImGui::SetNextItemWidth(75);
			ImGui::DragFloat("SnappDistance##SnappingDistanceIDSCENEWINDOW", &mySnappingDistance, 0.01f);
		}

		ImGui::SetCursorPosX(0);
	}

	void SceneWindow::GizmoManager(Transform2D* aTransform)
	{
		Math::Vector2f transformPos = aTransform->GetPosition();
		Math::Vector2f position = aTransform->GetPosition() * 0.5f + Math::Vector2f(0.5f, 0.5f);

		if (myGizmoMoveY)
			DebugDrawer::DrawArrow(position, Math::Vector2f(0, 1.f), 0.2f, 0.04f, Math::Color(0.2f, 1, 0.2f, 1));
		else
			DebugDrawer::DrawArrow(position, Math::Vector2f(0, 1.f), 0.2f, 0.04f, Math::Color(0, 1, 0, 1));

		if (myGizmoMoveX)
			DebugDrawer::DrawArrow(position, Math::Vector2f(1.f, 0.f), 0.2f, 0.04f, Math::Color(1, 0.2f, 0.2f, 1));
		else
			DebugDrawer::DrawArrow(position, Math::Vector2f(1.f, 0.f), 0.2f, 0.04f, Math::Color(1, 0, 0, 1));

		if (ImGui::IsMouseClicked(0))
		{
			float transformedGOPositionX = position.x - myInspectorPosition.x;
			float transformedGOPositionY = position.y - myInspectorPosition.y;

			float aspectRatio = myWindowSize.y / myWindowSize.x;

			float normMousePosX = windowRelativeMousePosition.x / myWindowSize.x;
			float normMousePosY = windowRelativeMousePosition.y / myWindowSize.y;

			float transformedMousePositionX = normMousePosX;
			float transformedMousePositionY = normMousePosY;

			float mouseXDistance = transformedGOPositionX - transformedMousePositionX;
			float mouseYDistance = transformedGOPositionY - transformedMousePositionY;

			float absXPos = std::abs(mouseXDistance);
			float absYPos = std::abs(mouseYDistance);

			if (absXPos < 0.1f)
			{
				myGizmoMoveY = true;
			}
			if (absYPos < 0.1f)
			{
				myGizmoMoveX = true;
			}
		}
	}

	void SceneWindow::Update()
	{
		ImVec2 windowSize = ImGui::GetWindowSize();
		myWindowSize = { windowSize.x, windowSize.y };

		if (ImGui::BeginMenuBar())
		{
			ObjectSnappingGizmo();
			DrawGizmoButtons(DrawGizmo);
			ImGui::EndMenuBar();
		}

		MouseManager();
		ZoomToObject();

		if (HierarchyWindow::CurrentGameObjectID)
		{
			mySelectedObject = GetComp(SpriteRenderer2D, HierarchyWindow::CurrentGameObjectID);

			if (mySelectedObject && mySelectedObject->GetMaterial())
			{
				Transform2D* transform = GetComp(Transform2D, HierarchyWindow::CurrentGameObjectID);

				DebugDrawer::Get().Begin();
				Math::Vector2f textureScale = mySelectedObject->GetMaterial()->myTexture->GetTextureSizeNormilized();
				Math::Vector2f size = mySelectedObject->spriteRectMax - mySelectedObject->spriteRectMin;
				float aspectScale = size.y / size.x;

				DebugDrawer::DrawSquare(transform->GetPosition() * 0.5f + Math::Vector2f(0.5f, 0.5f), transform->GetRotation(), transform->GetScale() * 0.005f * 0.5f * textureScale * Math::Vector2f(1.f, aspectScale), Math::Color(1.f, 0.4f, 0.7f, 1.f));

				//GizmoManager(transform);

				DebugDrawer::Get().Render();
			}
		}

		GraphicsEngine::BindFrameBuffer(mySceneFrameBuffer);

		if (Canvas::main)
		{
			float aspectRatio = myWindowSize.y / myWindowSize.x;
			Math::Vector2f CanvasResReference = Canvas::main->ReferenceResolution;

			Canvas::canvasCameraTransform.PositionOffset = (myInspectorPosition * -1.f) * CanvasResReference + Canvas::main->gameObject->transform->GetPosition() * CanvasResReference;
			Canvas::canvasCameraTransform.PositionOffset *= Math::Vector2f(aspectRatio, 1.f) * myInspectorScale;
			Canvas::canvasCameraTransform.Rotation = myInspectorRotation;
			Canvas::canvasCameraTransform.ScaleMultiplier = Math::Vector2f(myInspectorScale.x * aspectRatio * 2.f * 0.888f, myInspectorScale.y) * Canvas::main->gameObject->transform->GetScale();
		}

		Math::Vector2f lastInspectorPosition(0, 0);
		float lastInspectorRotation = 0;
		Math::Vector2f lastInspectorScale(1, 1);

		GraphicsEngine::GetGlobalUniform(UniformType::Vector2f, "cameraPosition", &lastInspectorPosition);
		GraphicsEngine::GetGlobalUniform(UniformType::Float, "cameraRotation", &lastInspectorRotation);
		GraphicsEngine::GetGlobalUniform(UniformType::Vector2f, "cameraScale", &lastInspectorScale);

		GraphicsEngine::UpdateGlobalUniform(UniformType::Vector2f, "cameraPosition", &myInspectorPosition);
		GraphicsEngine::UpdateGlobalUniform(UniformType::Float, "cameraRotation", &myInspectorRotation);
		GraphicsEngine::UpdateGlobalUniform(UniformType::Vector2f, "cameraScale", &myInspectorScale);

		float aspectRatio = myWindowSize.y / myWindowSize.x;
		GraphicsEngine::UpdateGlobalUniform(UniformType::Float, "resolutionRatio", &aspectRatio);

		glViewport(0, 0, myWindowSize.x, myWindowSize.y);

		// This is not using its own framebuffer but if left click then render and get mouse position color
		SpriteSelecter();

		int notOvColor = 1;
		GraphicsEngine::UpdateGlobalUniform(UniformType::Int, "notOverrideColor", &notOvColor);

		GraphicsEngine::ClearCurrentSceneBuffer();

		CommandListManager::GetSpriteCommandList().Execute();
		CommandListManager::GetUICommandList().Execute();
		CommandListManager::GetDebugDrawCommandList().Execute();

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

		if (Input::GetKeyDown(Keycode::DELETE_KEY))
		{
			GameObject currentObject = HierarchyWindow::CurrentGameObjectID;
			if (currentObject > 0)
				ComponentManager::Destroy(currentObject);

			HierarchyWindow::CurrentGameObjectID = 0;
		}

		Canvas::canvasCameraTransform.PositionOffset = { 0, 0 };
		Canvas::canvasCameraTransform.Rotation = 0.f;
		Canvas::canvasCameraTransform.ScaleMultiplier = { 1, 1 };
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
		// unsigned vertexShaderID = 0;
		// unsigned pixelShaderID = 0;

		//ResourcePointer<VertexShader> myVertexShader = Resources::Get<VertexShader>((PathManager::GetEngineAssets() / "Default/Shaders/SelectedVertexSpriteShader.glsl").generic_string().c_str());
		//ResourcePointer<PixelShader> myPixelShader = Resources::Get<PixelShader>((PathManager::GetEngineAssets() / "Default/Shaders/SelectedPixelSpriteShader.glsl").generic_string().c_str());

		// mySelectedSpriteHighlightProgram = glCreateProgram();
		// glAttachShader(mySelectedSpriteHighlightProgram, myVertexShader->GetVertexShaderID());
		// glAttachShader(mySelectedSpriteHighlightProgram, myPixelShader->GetPixelShaderID());
		// glLinkProgram(mySelectedSpriteHighlightProgram);
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