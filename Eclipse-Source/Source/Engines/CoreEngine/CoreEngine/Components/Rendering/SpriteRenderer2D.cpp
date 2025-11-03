#include "SpriteRenderer2D.h"

#include "Components/Transform2D.h"

#include "AssetManagement/Resources/Shaders/Shader.h"
#include "GraphicsEngine/Sprite.h"

#include "AssetManagement/Resources/Texture.h"

#include "GraphicsEngine/OpenGL/OpenGLGraphicsAPI.h"
#include "GraphicsEngine/RenderCommands/CommandList.h"

#include "RenderCommands/RenderSprite2DCommand.h"

#include "OpenGL/glad/glad.h"

#include "AssetEngine/PathManager.h"
#include "AssetEngine/Resources.h"

namespace Eclipse
{
	COMPONENT_REGISTRATION(SpriteRenderer2D);

	void SpriteRenderer2D::SetSpriteRect(const Math::Vector2f& aMin, const Math::Vector2f& aMax)
	{
		spriteRectMin = aMin * material.GetTexture().GetDimDivOne();
		spriteRectMax = aMax * material.GetTexture().GetDimDivOne();
	}

	void SpriteRenderer2D::SetTexture(const char* aPath)
	{
		sprite = Assets::Resourcess::Get<Textures>(aPath);
		hasTexture = true;
	}

	void SpriteRenderer2D::SetTexture(const size_t& id)
	{
		sprite = Assets::Resourcess::Get<Textures>(id);
		hasTexture = true;
	}

	void SpriteRenderer2D::SetMaterial(const char* aPath)
	{
		material = Assets::Resourcess::Get<Materials>(aPath);
		hasTexture = true;
	}

	void SpriteRenderer2D::SetMaterial(const size_t& id)
	{
		material = Assets::Resourcess::Get<Materials>(id);
		hasTexture = true;
	}

	void SpriteRenderer2D::OnComponentAdded()
	{
		material = Assets::Resourcess::GetDefaultMaterial();
		hasMaterial = true;
	}

	void SpriteRenderer2D::Start()
	{

	}

	void SpriteRenderer2D::Render()
	{
		CommandListManager::GetSpriteCommandList().Enqueue<RenderSprite2DCommand>(this);
		DebugInformationCollector::UpdateRenderCalls();
	}

	void SpriteRenderer2D::Draw(unsigned aProgramID)
	{
		if (!hasMaterial)
			return;

		Math::Vector2f position = gameObject->transform->GetPosition();
		float rotation = gameObject->transform->GetRotation();
		Math::Vector2f scale = gameObject->transform->GetScale();

		unsigned shaderID = material.GetShaderProgramID();

		if (aProgramID)
			shaderID = aProgramID;

		if (hasTexture)
		{
			material.BindShader();
			sprite.Bind();
			material.BindColor();
		}
		else
		{
			material.Use();
		}


		GraphicsEngine::SetUniform(UniformType::Vector2f, shaderID, "transform.position", &position);
		GraphicsEngine::SetUniform(UniformType::Float, shaderID, "transform.rotation", &rotation);
		GraphicsEngine::SetUniform(UniformType::Vector2f, shaderID, "transform.size", &scale);

		Math::Vector2f size = spriteRectMax - spriteRectMin;
		Math::Vector4f spriteRect = { spriteRectMin.x, spriteRectMin.y, size.x, size.y };
		GraphicsEngine::SetUniform(UniformType::Vector4f, shaderID, "material.spriteRect", &spriteRect);

		Math::Vector2f scaleMultiplier;
		if (hasTexture)
		{
			scaleMultiplier = sprite.GetTextureSizeNormilized();
		}
		else
		{
			scaleMultiplier = material.GetTexture().GetTextureSizeNormilized();
		}

		float aspectScale = size.y / size.x;
		Math::Vector2f spriteScaleMultiplier = { scaleMultiplier.x, scaleMultiplier.y * aspectScale };
		GraphicsEngine::SetUniform(UniformType::Vector2f, shaderID, "spriteScaleMultiplier", &spriteScaleMultiplier);

		Math::Vector2f mirroredVec2 = { mirroredX ? -1.f : 1.f, mirroredY ? -1.f : 1.f };
		GraphicsEngine::SetUniform(UniformType::Vector2f, shaderID, "mirrored", &mirroredVec2);

		Math::Vector4f pixelPickColor = gameObject->GetPixelPickingIDColor();
		GraphicsEngine::SetUniform(UniformType::Vector4f, shaderID, "pixelPickColor", &pixelPickColor);

		GraphicsEngine::SetGlobalUniforms(shaderID);

		Sprite::Get().Render();
	}
}