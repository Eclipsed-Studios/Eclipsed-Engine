#include "TextRenderer.h"

#include "RenderCommands/CommandList.h"

#include "AssetManagement/Resources/Shaders/Shader.h"
#include "Sprite.h"
#include "OpenGL/OpenGLGraphicsAPI.h"

#include "TextManager.h"

namespace Eclipse
{
	TextMaterial::TextMaterial()
	{
		myShader = new Shader();
		myShader->Create("Assets/Shaders/TextPixelShader.glsl", "Assets/Shaders/TextVertexShader.glsl");

		int yes = 1;
		GraphicsEngine::SetUniform(UniformType::Int, myShader->GetProgramID(), "TextTexture", &yes);
	}

	void TextMaterial::Use(unsigned textureID)
	{
		glActiveTexture(GL_TEXTURE0);
		GraphicsEngine::BindTexture(GL_TEXTURE_2D, textureID);
	}

	void TextRenderer::EditorUpdate()
	{
		if (myLastFontSize != myFontSize)
		{
			SetFontSize(myFontSize);
			myLastFontSize = myFontSize;
		}
		
	}

	void TextRenderer::OnComponentAdded()
	{
		OnSceneLoaded();
	}

	void TextRenderer::OnSceneLoaded()
	{
		if (!myCreatedRenderer)
		{
			myMaterial = new TextMaterial();
			myFont = &TextManager::Get().GetFont(myFontPath->c_str(), myFontSize);

			myCreatedRenderer = true;

			int lastFontSize = myFontSize;
		}
	}

	void TextRenderer::Draw()
	{
		if (!myMaterial)
			return;

		const char* textInConstChar = myText->c_str();

		Math::Vector2f position = gameObject->transform->GetPosition();
		float rotation = gameObject->transform->GetRotation();
		Math::Vector2f scale = gameObject->transform->GetScale();

		unsigned shaderID = myMaterial->myShader->GetProgramID();
		myMaterial->myShader->Use(shaderID);

		GraphicsEngine::SetUniform(UniformType::Vector2f, shaderID, "transform.position", &position);
		GraphicsEngine::SetUniform(UniformType::Float, shaderID, "transform.rotation", &rotation);
		GraphicsEngine::SetUniform(UniformType::Vector2f, shaderID, "transform.size", &scale);
		GraphicsEngine::SetGlobalUniforms(shaderID);

		Font& font = TextManager::Get().GetFont(myFontPath->c_str(), myFontSize);

		Math::Vector2f textOffset = { 0, 0 };
		for (int i = 0; i < myText->size(); i++)
		{
			char character = textInConstChar[i];

			if (character == (char)32)
			{
				textOffset += {0.5f, 0.f};
				continue;
			}

			Character& characterFace = font.myCharTexture.at(character);
			myMaterial->Use(characterFace.textureID);

			Math::Vector2f textSize = { (float)characterFace.size.x, (float)characterFace.size.y };
			GraphicsEngine::SetUniform(UniformType::Vector2f, shaderID, "size", &textSize);

			Math::Vector2f characterSpecificOffset = textOffset;
			characterSpecificOffset.y += characterFace.bearing.y * 0.01f;
			characterSpecificOffset.x -= characterFace.bearing.x * 0.05f;
			GraphicsEngine::SetUniform(UniformType::Vector2f, shaderID, "offset", &characterSpecificOffset);

			textOffset.x += (float)(characterFace.advance >> 6) * 0.02f * scale.x;

			Sprite::Get().Render();
		}
	}

	void TextRenderer::Render()
	{
		CommandListManager::GetSpriteCommandList().Enqueue([&]() {
			this->Draw();
			});
	}

	void TextRenderer::SetFontSize(int aFontSize)
	{
		myFontSize = aFontSize;

		myFont = &TextManager::Get().GetFont(myFontPath->c_str(), myFontSize);
	}

	void TextRenderer::SetFont(const char* aFont)
	{
		myFontPath = aFont;
		myFont = &TextManager::Get().GetFont(myFontPath->c_str(), myFontSize);
	}

	void TextRenderer::SetText(const char* aText)
	{
		myText = aText;
	}
}