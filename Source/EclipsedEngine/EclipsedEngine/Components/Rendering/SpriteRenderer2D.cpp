#include "SpriteRenderer2D.h"

#include "EclipsedEngine/Components/Transform2D.h"
#include "Renderer/Sprite.h"

#include "Renderer/OpenGL/OpenGLGraphicsAPI.h"
#include "Renderer/RenderCommands/CommandList.h"

#include "RenderCommands/RenderSprite2DCommand.h"

#include "OpenGL/glad/glad.h"

#include "Core/GraphicsBuffers/EditorBuffer.h"

namespace Eclipse
{
	void SpriteRenderer2D::SetColor(Math::Color color)
	{
		Albedo = color;
	}

	Math::Color SpriteRenderer2D::GetColor()
	{
		return Albedo.Get();
	}

	void SpriteRenderer2D::SetSpriteRect(const Math::Vector2f& aMin, const Math::Vector2f& aMax)
	{
		spriteRectMin = aMin * sprite->GetDimDivOne();
		spriteRectMax = aMax * sprite->GetDimDivOne();
	}

	void SpriteRenderer2D::SetXMirror(bool aMirror)
	{
		mirroredX = aMirror;
	}
	void SpriteRenderer2D::SetYMirror(bool aMirror) { mirroredY = aMirror; }

#pragma region --- Set Sprite
	void SpriteRenderer2D::SetSprite(const Assets::GUID& aGuid)
	{
		assert("No loading assets implemented.");
		//sprite = Resources::Get<Eclipse::Texture>(aGuid);
		hasSprite = true;

		//REPLICATEGARANTIED(sprite);
	}

	void SpriteRenderer2D::SetSprite(const Assets::Texture& aSprite)
	{
		sprite = aSprite;
		hasSprite = true;

		//REPLICATEGARANTIED(sprite);
	}
#pragma endregion
	void SpriteRenderer2D::SetMaterial(const Assets::GUID& aGuid)
	{
		assert("No loading assets implemented.");
		//material = Resources::Get<Assets::Material>(aGuid);
		hasMaterial = true;
	}

	void SpriteRenderer2D::SetMaterial(const Assets::Material& aMaterial)
	{
		material = aMaterial;
		hasMaterial = true;
	}


	Assets::Texture SpriteRenderer2D::GetSprite()
	{
		return sprite;
	}

	void SpriteRenderer2D::OnComponentAdded()
	{
		if (material->IsValid()) hasMaterial = true;
		if (sprite->IsValid()) hasSprite = true;

		if (!hasMaterial)
		{
			material = Assets::AssetManager::LoadDefault<Assets::Material>(Assets::DefaultAssetType::MATERIAL_2D_SPRITE);
			hasMaterial = true;
		}
	}

	void SpriteRenderer2D::Render()
	{
		if (!gameObject->transform)
			return;

		CommandListManager::GetSpriteCommandList().Enqueue<RenderSprite2DCommand>(this);
		//DebugInformationCollector::UpdateRenderCalls();
	}

	void SpriteRenderer2D::Draw(unsigned aProgramID)
	{
		if (!hasMaterial || IsDeleted)
			return;

		// unsigned shaderID = material->GetShaderProgramID();
		//
		// if (aProgramID)
		// 	shaderID = aProgramID;

		if (sprite->IsValid())
		{
			material->BindShader();
			sprite->Bind();

			material->dataPtr->color = Albedo;
			material->BindColor();
		}
		else
		{
			material->Use();

			material->dataPtr->color = Albedo;
			material->BindColor();
		}
		
		myTransformBuffer.Position = gameObject->transform->GetPosition();
		myTransformBuffer.Rotation = gameObject->transform->GetRotation();
		myTransformBuffer.Scale = gameObject->transform->GetScale();

		Math::Vector2f NewSpriteRectMax = spriteRectMax;
		Math::Vector2f NewSpriteRectMin = spriteRectMin;

		NewSpriteRectMax.y = 1 - NewSpriteRectMax.y;
		NewSpriteRectMin.y = 1 - NewSpriteRectMin.y;

		Math::Vector2f size = NewSpriteRectMax - NewSpriteRectMin;
		material->materialBuffer.spriteRect = { NewSpriteRectMin.x, NewSpriteRectMin.y, size.x, size.y };

		Math::Vector2f scaleMultiplier;
		if (sprite->IsValid())
			scaleMultiplier = sprite->GetTextureSizeNormilized();
		else
			scaleMultiplier = material->GetTexture().GetTextureSizeNormilized();


		float aspectScale = size.y / size.x;
		mySpriteBuffer.spriteScaleMultiplier = { scaleMultiplier.x, scaleMultiplier.y * aspectScale };
		mySpriteBuffer.mirrored = { mirroredX ? -1.f : 1.f, mirroredY ? -1.f : 1.f };

		BaseGraphicsBuffer* graphicsBuffer = GraphicsEngine::Get()->GetGraphicsBuffer();

#ifdef ECL_EDITOR
		EditorBuffer* editorBuffer;
		graphicsBuffer->GetBuffer<EditorBuffer>(editorBuffer);
		editorBuffer->PixelPickColor = gameObject->myPixelPickColor;
		graphicsBuffer->SetOrCreateBuffer<EditorBuffer>(35);
#endif
		graphicsBuffer->SetOrCreateBuffer(5, material->materialBuffer);
		
		graphicsBuffer->SetOrCreateBuffer(1, myTransformBuffer);
		graphicsBuffer->SetOrCreateBuffer(3, mySpriteBuffer);

		Sprite::Get().Render();
	}
}
