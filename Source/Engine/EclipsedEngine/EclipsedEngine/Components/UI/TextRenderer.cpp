#include "TextRenderer.h"

#include "GraphicsEngine/RenderCommands/CommandList.h"

#include "GraphicsEngine/TextSprite.h"
#include "GraphicsEngine/OpenGL/OpenGLGraphicsAPI.h"

#include "EclipsedEngine/Components/UI/RectTransform.h"
#include "EclipsedEngine/Components/UI/Canvas.h"

#include "OpenGL/glad/gl.h"

#include "AssetEngine/Core/EditorAssetDatabase.h"
#include "AssetEngine/AssetManager.h"
#include "CoreEngine/MainSingleton.h"
#include "CoreEngine/GraphicsBuffers/TextMaterialBuffer.h"
#include "CoreEngine/GraphicsBuffers/TransformBuffer.h"

#include "AssetEngine/AssetManager.h"

namespace Eclipse
{
	//TextMaterial::TextMaterial()
	//{
		//
		//const Assets::AssetMeta& VtxShaderGUID = MainSingleton::GetInstance<Assets::AssetDatabase>().GetProcessedFile("Default/Shaders/Text.vglsl");
		//const Assets::AssetMeta& PxShaderGUID = MainSingleton::GetInstance<Assets::AssetDatabase>().GetProcessedFile("Default/Shaders/Text.pglsl");

		//pixelShader = Assets::AssetManager::Load<Assets::PixelShader>(PxShaderGUID.guid);
		//vertexShader = Assets::AssetManager::Load<Assets::VertexShader>(VtxShaderGUID.guid);

		//programID = glCreateProgram();
		//glAttachShader(programID, vertexShader.GetProgramID());
		//glAttachShader(programID, pixelShader.GetProgramID());
		//glLinkProgram(programID);
	//}

	//void TextMaterial::Use(unsigned textureID)
	//{
	//	glActiveTexture(GL_TEXTURE0);
	//	GraphicsEngine::Get<OpenGLGraphicsEngine>()->BindTexture(GL_TEXTURE_2D, textureID);
	//}




#ifdef ECLIPSED_EDITOR
	void TextRenderer::EditorUpdate()
	{
		// TODO: should be called form Comp manager
		OnDrawGizmos();

		if (myLastFontSize != myFontSize)
		{
			myLastFontSize = myFontSize;
		}

	}
#endif

	void TextRenderer::TransformUpdate()
	{
		auto tranform = gameObject->GetComponent<RectTransform>();

		Canvas* canvas = tranform->myCanvas;
		if (!canvas)
		{
			tranform->myIsDirty = false;
			return;
		}
		
		Canvas::EditorCanvasCameraTransform& canvasCameraTransform = canvas->canvasCameraTransform;
		Math::Vector2f resolution = canvas->ReferenceResolution;
		Math::Vector2f canvasScaleRelationOneDiv = { 1.f / resolution.x, 1.f / resolution.y };
		
		myTransformBuffer.Position = tranform->GetPosition();
		if (IsScene)
			myTransformBuffer.Position *= canvasCameraTransform.ScaleMultiplier;
		else
			myTransformBuffer.Position *= Math::Vector2f(2, 2);
		myTransformBuffer.Position += canvasCameraTransform.PositionOffset;
		
		myTransformBuffer.Scale = tranform->WidthHeightPX.Get() * canvasScaleRelationOneDiv * ((float)myFontSize * 0.005f);
		// if (!IsScene)
		// 	myTransformBuffer.Scale *= { 2.f, 2.f };
		
		Math::Vector2f multiplier;
		if (IsScene)
			multiplier = canvasCameraTransform.ScaleMultiplier;
		else
		{
			if (!tranform->ScaleWithCanvasX)
				multiplier.x = canvasCameraTransform.ScaleMultiplier.x;
			else
				multiplier.x = 2;
			if (!tranform->ScaleWithCanvasY)
				multiplier.y = canvasCameraTransform.ScaleMultiplier.y;
			else
				multiplier.y = 2;
		}
		myTransformBuffer.Scale *= multiplier;

		
		myTransformBuffer.Scale.x *= 2.f;
		
		myTransformBuffer.Rotation = canvasCameraTransform.Rotation;
	}


	void TextRenderer::OnComponentAdded()
	{
		material = Assets::AssetManager::LoadDefault<Assets::Material>(Assets::DefaultAssetType::MATERIAL_TEXT);

		gameObject->GetComponent<RectTransform>()->AddFunctionToRunOnDirtyUpdate([&](){
			TransformUpdate();
		});

		font = Assets::AssetManager::LoadDefault<Assets::Font>(Assets::DefaultAssetType::TEXT_FONT);
	}

	void TextRenderer::OnDrawGizmos()
	{
		// This is not right, does not work as intended
		
		if (drawRectGizmos)
		{
			auto tranform = gameObject->GetComponent<RectTransform>();
			if (!tranform)
				return;
			if (!tranform->myCanvas)
				return;
		
			Math::Vector2f resolution = tranform->myCanvas->ReferenceResolution;
			float aspectRatio = resolution.x / resolution.y;
			Math::Vector2f canvasScaleRelationOneDiv = { 1.f / resolution.x, 1.f / resolution.y };
		
			const Math::Vector2f& position = tranform->GetPosition() * canvasScaleRelationOneDiv * Math::Vector2f(aspectRatio, 1);
			//float rotation = gameObject->transform->GetRotation();
			Math::Vector2f scale = tranform->WidthHeightPX.Get() * myRect * canvasScaleRelationOneDiv;
			scale.x *= aspectRatio;

			//Math::Vector2f CanvasPosition = canvasScaleRelationOneDiv * tranform->myCanvas->canvasCameraTransform.PositionOffset * 0.5f;
		
			DebugDrawer::DrawSquare(position + Math::Vector2f(0.5f, 0.5f), 0.f, scale, Math::Color(0.7f, 0.7f, 0.7f, 1.f));
		}
	}

	void TextRenderer::Render()
	{
		CommandListManager::GetUICommandList().Enqueue([&]() {
				this->Draw();
			});
	}

	void TextRenderer::Draw()
	{
		if (!material.IsValid())
			return;
		if (!font->dataPtr)
			return;

		const char* textInConstChar = myText->c_str();
		auto transform = gameObject->GetComponent<RectTransform>();

		if (!transform)
			return;
		if (!transform->myCanvas)
			return;

		// CameraBuffer* cameraBuffer = nullptr;
		// GraphicsEngine::Get<OpenGLGraphicsEngine>()->GetGraphicsBuffer()->GetBuffer<CameraBuffer>(cameraBuffer);
		
		transform->myCanvas->SetCanvasTransformProperties();
		material.Use();
		/*unsigned shaderID = ;
		glUseProgram(shaderID);*/
		
		Math::Vector2f resolution = transform->myCanvas->ReferenceResolution;

		auto CurrentFont = font->dataPtr->font;

		TransformUpdate();
		
		GraphicsEngine::Get<OpenGLGraphicsEngine>()->GetGraphicsBuffer()->SetOrCreateBuffer(1, myTransformBuffer);
		
		Math::Vector2f textOffset = { 0, 0 };
		Math::Vector2f scaleRect = myTransformBuffer.Scale * myRect * resolution;
		scaleRect.x *= 0.5f;
		
		lineOffsets.resize(1);
		lineOffsets.back() = 0;
		for (int i = 0; i < myText->size(); i++)
		{
			char character = textInConstChar[i];
			if (character == ' ')
			{
				float spaceOffset = myTransformBuffer.Scale.x * 50.f * 0.5f * myCharacterSpacing * myFontSize * mySpaceSpacing;
				lineOffsets.back() += spaceOffset;
				continue;
			}
			else if (character == '\n')
			{
				lineOffsets.emplace_back(0.f);
				continue;
			}
			Assets::Character& characterFace = CurrentFont.myCharTexture.at(character);
			float convertedAdvance = (float)(characterFace.advance >> 6) * 100.f * myTransformBuffer.Scale.x;
			lineOffsets.back() += convertedAdvance * 0.5f * myTextAlignment * myCharacterSpacing;
		}
		
		
		if (myTextAlignment == 0 || myTextAlignment == 3)
			textOffset.x -= scaleRect.x;
		else if (myTextAlignment == 2)
			textOffset.x += scaleRect.x - myTransformBuffer.Scale.x;
		
		Math::Vector2f startOffset = textOffset;
		if (myTextCentering == 0)
			;//textOffset.y = (scaleRect.y - myFontSize * 4.f);
		else if (myTextCentering == 1)
			;//textOffset.y = myFontSize * -3.f * lineOffsets.size();
		else if (myTextCentering == 2)
			;//textOffset.y = (-scaleRect.y + 0.0125f)  * lineOffsets.size();
		
		myTextMaterialBuffer.color = myTextColor;
		GraphicsEngine::Get<OpenGLGraphicsEngine>()->GetGraphicsBuffer()->SetOrCreateBuffer<TextMaterialBuffer>(5, myTextMaterialBuffer);

		
		int currentLineCount = 0;
		for (int i = 0; i < myText->size(); i++)
		{
			char character = textInConstChar[i];
		
			if (character == '\t')
			{
				textOffset.x += myTransformBuffer.Scale.x * 50.f * 4.f * myCharacterSpacing * myFontSize;
				continue;
			}
			else if (character == '\n')
			{
				textOffset.y -= myTransformBuffer.Scale.y * 50.f * myEnterSpacing * 2.f * myFontSize;
				textOffset.x = startOffset.x;
				currentLineCount++;
				continue;
			}
			else if (character == ' ')
			{
				textOffset.x += myTransformBuffer.Scale.x * 50.f * myCharacterSpacing * myFontSize * mySpaceSpacing;
				continue;
			}
		
		
			if (CurrentFont.myCharTexture.find(character) == CurrentFont.myCharTexture.end())
				character = '\n';
		
			Assets::Character& characterFace = CurrentFont.myCharTexture.at(character);
			float characterAdvance = (float)(characterFace.advance >> 6) * 100.f * myTransformBuffer.Scale.x;
		
			//Math::Vector2f scaleRect = myTransformBuffer.Scale * myRect * resolution;
			// float newXOffset = textOffset.x + characterAdvance;
			// if (newXOffset >= scaleRect.x)
			// {
			// 	return;
			// }
		
			glActiveTexture(GL_TEXTURE0);
			GraphicsEngine::Get<OpenGLGraphicsEngine>()->BindTexture(GL_TEXTURE_2D, characterFace.textureID);

			myTextBuffer.size = { (float)characterFace.size.x, (float)characterFace.size.y};
		
			float lineOffset;
			if (myTextAlignment == 0)
				lineOffset = 0;
			else
				lineOffset = lineOffsets[currentLineCount] - myTransformBuffer.Scale.x * myCharacterSpacing;
		
		
			myTextBuffer.offset = textOffset;
			myTextBuffer.offset.x += (characterFace.bearing.x * 100.f * myTransformBuffer.Scale.x) - lineOffset;
			myTextBuffer.offset.y -= (characterFace.size.y - characterFace.bearing.y) * myTransformBuffer.Scale.y * 100.f;

#ifdef ECLIPSED_EDITOR
			EditorBuffer* editorBuffer;
			GraphicsEngine::Get<OpenGLGraphicsEngine>()->GetGraphicsBuffer()->GetBuffer<EditorBuffer>(editorBuffer);
			editorBuffer->PixelPickColor = gameObject->GetPixelPickingIDColor();
			GraphicsEngine::Get<OpenGLGraphicsEngine>()->GetGraphicsBuffer()->SetOrCreateBuffer<EditorBuffer>(35);
#endif
			
			GraphicsEngine::Get<OpenGLGraphicsEngine>()->GetGraphicsBuffer()->SetOrCreateBuffer(3, myTextBuffer);
			textOffset.x += characterAdvance * myCharacterSpacing;

			CanvasBuffer* canvasBuffer;
			GraphicsEngine::Get<OpenGLGraphicsEngine>()->GetGraphicsBuffer()->GetBuffer<CanvasBuffer>(canvasBuffer);
			
			if (!IsScene)
			{
				if (!transform->myCanvas->WorldSpace)
					canvasBuffer->canvasPositionOffset = transform->myCanvas->canvasCameraTransform.PositionOffset;
				else
					canvasBuffer->canvasPositionOffset = {0, 0};
            
			}
			
			GraphicsEngine::Get<OpenGLGraphicsEngine>()->GetGraphicsBuffer()->SetOrCreateBuffer(2, *canvasBuffer);
			
			TextSprite::Get().Render();
		}
	}

	void TextRenderer::SetFontSize(float aFontSize)
	{
		myFontSize = aFontSize;
	}

	void TextRenderer::SetFont(const char* aFont)
	{
		
	}

	void TextRenderer::SetText(const char* aText)
	{
		myText = aText;
	}
}
