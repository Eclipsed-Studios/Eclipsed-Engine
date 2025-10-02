#include "SpriteRenderer2D.h"

#include "Components/Transform2D.h"

#include "AssetManagement/Resources/Shaders/Shader.h"
#include "Sprite.h"

#include "TemporarySettingsSingleton.h"

#include "AssetManagement/Resources/Texture.h"

#include "Debug/DebugInformationCollector.h"

#include "OpenGL/OpenGLGraphicsAPI.h"
#include "RenderCommands/CommandList.h"

#include "RenderCommands/RenderSprite2DCommand.h"

namespace Eclipse
{
	Material::Material()
	{
		myShader = new Shader();
		myShader->Create(ASSET_PATH "Shaders/DefaultSpritePixelShader.glsl", ASSET_PATH "Shaders/DefaultSpriteVertexShader.glsl");

		myTexture = Resources::Get<Texture>("Assets/Default_Texture.png");
	}

	void Material::SetTexture(const char* aPath)
	{
		myTexture = Resources::Get<Texture>(aPath);

		unsigned shaderID = myShader->GetProgramID();

		int none = 0;
		GraphicsEngine::SetUniform(UniformType::Int, shaderID, "material.albedo", &none);
	}

	void Material::Use()
	{
		glActiveTexture(GL_TEXTURE0);
		GraphicsEngine::BindTexture(GL_TEXTURE_2D, myTexture->GetTextureID());

		unsigned shaderID = myShader->GetProgramID();

		Math::Vector4f American_Colour = color.ToVector();
		GraphicsEngine::SetUniform(UniformType::Vector4f, shaderID, "material.color", &American_Colour);
	}

	void SpriteRenderer2D::SetSpriteRect(const Math::Vector2f& aMin, const Math::Vector2f& aMax)
	{
		spriteRectMin = aMin * myMaterial->myTexture->spriteDimDivOne;
		spriteRectMax = aMax * myMaterial->myTexture->spriteDimDivOne;
	}

	void SpriteRenderer2D::SetTexture(const char* aPath)
	{
		myTexturePath = aPath;

		if (myMaterial == nullptr)
		{
			myMaterial = new Material();
		}

		if (mySprite == nullptr)
		{
			mySprite = new Sprite();
			mySprite->Init();
		}

		hasTexture = true;
		myMaterial->SetTexture(myTexturePath->c_str());
	}

	void SpriteRenderer2D::OnSceneLoaded()
	{
		if (mySprite == nullptr)
		{
			mySprite = new Sprite();
		}

		mySprite->Init();

		if (myMaterial == nullptr)
		{
			myMaterial = new Material();
		}
		myMaterial->SetTexture(myTexturePath->c_str());

		//myTexturePath = myTexturePath->c_str();

		//Transform2D& localTransform = *gameObject->transform;
		//Math::Vector2f textureSizeNormalized = myMaterial->myTexture->GetTextureSizeNormilized();
		//Math::Vector2f scale = localTransform.GetScale();

		//localTransform.SetScale(textureSizeNormalized * scale);
	}

	void SpriteRenderer2D::Start()
	{

	}

	void SpriteRenderer2D::Render()
	{
		CommandList::Enqueue<RenderSprite2DCommand>(this);
		DebugInformationCollector::UpdateRenderCalls();
	}

	void SpriteRenderer2D::Draw(unsigned aProgramID)
	{
		if (!myMaterial)
			return;
		if (!mySprite)
			return;

		Math::Vector2f position = gameObject->transform->GetPosition();
		float rotation = gameObject->transform->GetRotation();
		Math::Vector2f scale = gameObject->transform->GetScale();

		unsigned shaderID = myMaterial->myShader->GetProgramID();

		if (aProgramID)
			shaderID = aProgramID;

		myMaterial->myShader->Use(shaderID);
		myMaterial->Use();

		GraphicsEngine::SetUniform(UniformType::Vector2f, shaderID, "transform.position", &position);
		GraphicsEngine::SetUniform(UniformType::Float, shaderID, "transform.rotation", &rotation);
		GraphicsEngine::SetUniform(UniformType::Vector2f, shaderID, "transform.size", &scale);

		Math::Vector2f size = spriteRectMax - spriteRectMin;
		Math::Vector4f spriteRect = { spriteRectMin.x, spriteRectMin.y, size.x, size.y };
		GraphicsEngine::SetUniform(UniformType::Vector4f, shaderID, "material.spriteRect", &spriteRect);

		float aspectScale = size.y / size.x;
		Math::Vector2f scaleMultiplier = myMaterial->myTexture->GetTextureSizeNormilized();
		Math::Vector2f spriteScaleMultiplier = { scaleMultiplier.x, scaleMultiplier.y * aspectScale };
		GraphicsEngine::SetUniform(UniformType::Vector2f, shaderID, "spriteScaleMultiplier", &spriteScaleMultiplier);

		Math::Vector2f mirroredVec2 = { mirroredX ? -1.f : 1.f, mirroredY ? -1.f : 1.f };
		GraphicsEngine::SetUniform(UniformType::Vector2f, shaderID, "mirrored", &mirroredVec2);

		Math::Vector4f pixelPickColor = gameObject->GetPixelPickingIDColor();
		GraphicsEngine::SetUniform(UniformType::Vector4f, shaderID, "pixelPickColor", &pixelPickColor);

		GraphicsEngine::SetGlobalUniforms(shaderID);

		GraphicsEngine::SetGlobalUniforms(shaderID);

		mySprite->Render();
	}
}