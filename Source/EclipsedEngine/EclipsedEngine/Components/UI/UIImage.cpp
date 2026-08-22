#include "UIImage.h"

#include "Renderer/Sprite.h"

#include "Assets/AssetManager.h"
#include "Core/Settings/GraphicsSettings.h"

#include "EclipsedEngine/Components/UI/RectTransform.h"
#include "EclipsedEngine/Components/UI/Canvas.h"

#include "Renderer/RenderCommands/CommandList.h"

#include "Renderer/OpenGL/OpenGLGraphicsAPI.h"

#ifdef ECL_EDITOR
#include "Renderer/OpenGL/DebugDrawers/DebugDrawer.h"
#include <Core/GraphicsBuffers/EditorBuffer.h>
#include "EclipsedEngine/Editor/Windows/WindowTypes/GameWindow.h"
#endif // ECL_EDITOR


namespace Eclipse
{
#ifdef ECL_EDITOR
	void UIImage::EditorUpdate()
	{
		auto transform = gameObject->GetComponent<RectTransform>();

		if (transform->myCanvas)
		{
			float sizeX = (transform->WidthHeightPX->x / transform->myCanvas->ReferenceResolution->y) * 0.5f;
			float sizeY = (transform->WidthHeightPX->y / transform->myCanvas->ReferenceResolution->y) * 0.5f;

			float posX = transform->Position->x / transform->myCanvas->ReferenceResolution->y + 0.5f;
			float posY = transform->Position->y / transform->myCanvas->ReferenceResolution->y + 0.5f;

			Math::Vector2f sqrPos = { posX, posY };
			Math::Vector2f sqrSize = { sizeX, sizeY };

			DebugDrawer::DrawSquare(sqrPos + transform->myCanvas->canvasCameraTransform.PositionOffset, 0, sqrSize, Math::Color(0x90D5FF));
		}
	}
#endif // ECL_EDITOR
	void UIImage::OnComponentAdded()
	{
		if (material->IsValid()) hasMaterial = true;
		if (sprite->IsValid()) hasSprite = true;

		if (!hasMaterial)
		{
			material = Assets::AssetManager::LoadDefault<Assets::Material>(Assets::DefaultAssetType::MATERIAL_UI);
			hasMaterial = true;
		}
	}

	void UIImage::Render()
	{
		CommandListManager::GetUICommandList().Enqueue([&]()
			{
				Draw();
			});
	}

	void UIImage::TransformUpdate()
	{
		auto tranform = gameObject->GetComponent<RectTransform>();

		Canvas* canvas = tranform->myCanvas;
		if (!canvas)
		{
			tranform->myIsDirty = false;
			return;
		}

		Canvas::EditorCanvasCameraTransform& canvasCameraTransform = canvas->canvasCameraTransform;
		Math::Vector2f referenceResolution = canvas->ReferenceResolution;
		Math::Vector2f halfRefRes = referenceResolution * 0.5f;

#ifdef ECL_EDITOR
		Math::Vector2f resolution = Editor::GameWindow::myGameImageResolution;
#else
		Math::Vector2f resolution = Settings::GraphicsSettings::GetResolution();
#endif

		Math::Vector2f resMinRef = resolution - referenceResolution;

		Math::Vector2f halfRes = resolution * 0.5f;
		Math::Vector2f position = tranform->GetPosition();

		myTransformBuffer.Position = position;

#ifdef ECL_EDITOR
		if (IsScene)
			myTransformBuffer.Position *= canvasCameraTransform.ScaleMultiplier;
		else
#endif
			myTransformBuffer.Position *= Math::Vector2f(2, 2);

		myTransformBuffer.Position += canvasCameraTransform.PositionOffset;

		Math::Vector2f WidthHeightPX = tranform->WidthHeightPX.Get();
		myTransformBuffer.Scale = WidthHeightPX;

		Math::Vector2f canvasScaleRelationOneDiv = { 1.f / referenceResolution.x, 1.f / referenceResolution.y };
		myTransformBuffer.Scale *= canvasScaleRelationOneDiv;

		Math::Vector2f multiplier;

#ifdef ECL_EDITOR
		if (IsScene)
			multiplier = canvasCameraTransform.ScaleMultiplier;
		else
		{
#endif
			if (!tranform->ScaleWithCanvasX)
				multiplier.x = canvasCameraTransform.ScaleMultiplier.x;
			else
				multiplier.x = 2;
			if (!tranform->ScaleWithCanvasY)
				multiplier.y = canvasCameraTransform.ScaleMultiplier.y;
			else
				multiplier.y = 2;

#ifdef ECL_EDITOR
		}
#endif
		myTransformBuffer.Scale *= multiplier;

		myTransformBuffer.Rotation = canvasCameraTransform.Rotation;
	}

	void UIImage::Draw()
	{

		if (!hasMaterial)
			return;


		auto transform = gameObject->GetComponent<RectTransform>();
		if (!transform)
			return;
		if (!transform->myCanvas)
			return;

		transform->myCanvas->SetCanvasTransformProperties();


		Math::Vector2f resolution = transform->myCanvas->ReferenceResolution;

		resolution.x = 1.f / resolution.x;
		resolution.y = 1.f / resolution.y;

		// float aspectRatio = resolution.y / resolution.x;
		// Math::Vector2f canvasScaleRelationOneDiv = {resolution.x, resolution.y};

		Math::Vector2f size = spriteRectMax - spriteRectMin;
		material->materialBuffer.spriteRect = { spriteRectMin.x, spriteRectMin.y, size.x, size.y };

		if (sprite->IsValid())
		{
			material->BindShader();
			sprite->Bind();
			material->BindColor();
		}
		else
		{
			material->Use();
		}

		TransformUpdate();


		BaseGraphicsBuffer* graphicsBuffer = GraphicsEngine::Get()->GetGraphicsBuffer();

		CanvasBuffer* canvasBuffer;
		graphicsBuffer->GetBuffer<CanvasBuffer>(canvasBuffer);

#ifdef ECL_EDITOR
		EditorBuffer* editorBuffer;
		graphicsBuffer->GetBuffer<EditorBuffer>(editorBuffer);
		editorBuffer->PixelPickColor = gameObject->myPixelPickColor;
		graphicsBuffer->SetOrCreateBuffer<EditorBuffer>(35);

		if (!IsScene)
		{
#endif
			if (!transform->myCanvas->WorldSpace)
				canvasBuffer->canvasPositionOffset = transform->myCanvas->canvasCameraTransform.PositionOffset;
			else
				canvasBuffer->canvasPositionOffset = { 0, 0 };
#ifdef ECL_EDITOR
		}
#endif


		graphicsBuffer->SetOrCreateBuffer(5, material->materialBuffer);
		graphicsBuffer->SetOrCreateBuffer(1, myTransformBuffer);

		graphicsBuffer->SetOrCreateBuffer(2, *canvasBuffer);

		Sprite::Get().Render();
	}
}
