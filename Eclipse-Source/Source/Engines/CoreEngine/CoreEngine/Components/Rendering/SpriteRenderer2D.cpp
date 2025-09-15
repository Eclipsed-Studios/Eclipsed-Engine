#include "SpriteRenderer2D.h"

#include "Components/Transform2D.h"

#include "Math/Vector/Vector2.h"

#include "AssetManagement/Resources/Shaders/Shader.h"
#include "Sprite.h"

#include "ECS/ComponentManager.h"

// Temporary dont use setuniforms
#include "glad/glad.h"
#include "TemporarySettingsSingleton.h"

#include "AssetManagement/Resources/Texture.h"

#include "Debug/DebugInformationCollector.h"

#include "OpenGL/OpenGLGraphicsAPI.h"
#include "RenderCommands/CommandList.h"

#include "RenderCommands/RenderSprite2DCommand.h"

#include "Editor/DragAndDrop.h"
#include "ImGui/ImGui/imgui.h"

namespace Eclipse
{
	Material::Material()
	{
		myShader = new Shader();
		myShader->Create(ASSET_PATH "Shaders/DefaultSpritePixelShader.glsl", ASSET_PATH "Shaders/DefaultSpriteVertexShader.glsl");

		myTexture = Resources::Get<Texture>(ASSET_PATH "Default_Texture.png");
	}

	void Material::SetTexture(const char* aPath)
	{
		myTexture = Resources::Get<Texture>(aPath);

		unsigned shaderID = myShader->GetProgramID();

		GLint diffuseIndex = glGetUniformLocation(shaderID, "material.albedo");
		glUniform1i(diffuseIndex, 0);
	}

	void Material::Use()
	{
		myShader->Use();

		glActiveTexture(GL_TEXTURE0);
		GraphicsEngine::BindTexture(GL_TEXTURE_2D, myTexture->GetTextureID());

		unsigned shaderID = myShader->GetProgramID();

		GLint albedoColorIndex = glGetUniformLocation(shaderID, "material.color");
		glUniform4f(albedoColorIndex, color.r, color.g, color.b, color.a);
	}

	void SpriteRenderer2D::SetSpriteRect(const Math::Vector2f& aMin, const Math::Vector2f& aMax)
	{
		spriteRectMin = aMin * myMaterial->myTexture->spriteDimDivOne;
		spriteRectMax = aMax * myMaterial->myTexture->spriteDimDivOne;
	}

	void SpriteRenderer2D::DrawInspector()
	{
		//bool hasSprite = 
		//Editor::DragAndDrop::TextBox(hasAudioClip ? myAudioClip->GetRelativePath() : "No audio clip", { 5, 5 }, { 0,0,0,0 }, { 255, 255,255, 1 }, "audioClipDND");

		//if (ImGui::BeginDragDropTarget())
		//{
		//	int idx = (int)Editor::DragAndDrop::AssetDragAndDropIdx::Audio;
		//	const char* dndString = Editor::DragAndDrop::dragAndDropString[idx];

		//	if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(dndString))
		//	{
		//		std::string path;
		//		path.resize(payload->DataSize);

		//		memcpy(path.data(), payload->Data, payload->DataSize);
		//		SetAudioClip(path.c_str());

		//	}
		//	ImGui::EndDragDropTarget();
		//}
	}

	void SpriteRenderer2D::SetTexture(const char* aPath)
	{
		myTexturePath = aPath;

		if (myMaterial != nullptr) myMaterial->SetTexture(myTexturePath->c_str());
	}

	void SpriteRenderer2D::Awake()
	{
		mySprite = new Sprite();
		mySprite->Init();

		myMaterial = new Material();
		myMaterial->SetTexture(myTexturePath->c_str());

		myMaterial->color.g = 0;
		myMaterial->color.b = 0;

		Transform2D& localTransform = *gameObject->transform;
		Math::Vector2f textureSizeNormalized = myMaterial->myTexture->GetTextureSizeNormilized();
		Math::Vector2f scale = localTransform.GetScale();

		localTransform.SetScale(textureSizeNormalized * scale);
	}

	void SpriteRenderer2D::Start()
	{

	}

	void SpriteRenderer2D::Render()
	{
		CommandList::Enqueue<RenderSprite2DCommand>(this);
		DebugInformationCollector::UpdateRenderCalls();
	}

	void SpriteRenderer2D::Draw()
	{
		Math::Vector2f position = gameObject->transform->GetPosition();
		float rotation = gameObject->transform->GetRotation();
		Math::Vector2f scale = gameObject->transform->GetScale();

		unsigned shaderID = myMaterial->myShader->GetProgramID();

		myMaterial->Use();
		GLint positionIndex = glGetUniformLocation(shaderID, "transform.position");
		glUniform2f(positionIndex, position.x, position.y);
		GLint rotationIndex = glGetUniformLocation(shaderID, "transform.rotation");
		glUniform1f(rotationIndex, rotation);
		GLint scaleIndex = glGetUniformLocation(shaderID, "transform.size");
		glUniform2f(scaleIndex, scale.x, scale.y);

		Math::Vector2f size = spriteRectMax - spriteRectMin;

		GLint spriteRectIndex = glGetUniformLocation(shaderID, "material.spriteRect");
		glUniform4f(spriteRectIndex, spriteRectMin.x, spriteRectMin.y, size.x, size.y);

		GLint mirrored = glGetUniformLocation(shaderID, "mirrored");
		glUniform2f(mirrored, mirroredX ? -1.f : 1.f, mirroredY ? -1.f : 1.f);

		GraphicsEngine::SetGlobalUniforms(shaderID);

		mySprite->Render();
	}
}