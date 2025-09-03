#include "SpriteRendrer2D.h"

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

namespace ENGINE_NAMESPACE
{
    Material::Material()
    {
        myShader = new Shader();
        myShader->Create(ASSET_PATH "Shaders/DefaultSpritePixelShader.glsl", ASSET_PATH "Shaders/DefaultSpriteVertexShader.glsl");
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
        glBindTexture(GL_TEXTURE_2D, myTexture->GetTextureID());

        unsigned shaderID = myShader->GetProgramID();
        GLint albedoColorIndex = glGetUniformLocation(shaderID, "material.color");
        glUniform4f(albedoColorIndex, 
            color.GetComponent(Math::ColorComponent::Red), 
            color.GetComponent(Math::ColorComponent::Green), 
            color.GetComponent(Math::ColorComponent::Blue), 
            color.GetComponent(Math::ColorComponent::Alpha));
    }

    void SpriteRendrer2D::SetMaterial(Material* aMaterial)
    {
        myMaterial = aMaterial;
    }
    void SpriteRendrer2D::SetSpriteRect(const Math::Vector2f& aMin, const Math::Vector2f& aMax)
    {
        spriteRectMin = aMin * myMaterial->myTexture->spriteDimDivOne;
        spriteRectMax = aMax * myMaterial->myTexture->spriteDimDivOne;
    }

    void SpriteRendrer2D::Awake()
    {
        mySprite = new Sprite();
        mySprite->Init();
    }

    void SpriteRendrer2D::Start()
    {
        myTransform = ComponentManager::GetComponent<Transform2D>(gameObject);
    }

    void SpriteRendrer2D::LateUpdate()
    {
        unsigned shaderID = myMaterial->myShader->GetProgramID();

        auto& settings = TemporarySettingsSingleton::Get();

        float resX = settings.GetOneDivResolutionX();
        float resY = settings.GetOneDivResolutionY();

        Math::Vector2f position = myTransform->GetPosition();
        float rotation = myTransform->GetRotation();
        Math::Vector2f scale = myTransform->GetScale();

        GLint positionIndex = glGetUniformLocation(shaderID, "transform.position");
        glUniform2f(positionIndex, position.x, position.y);
        GLint rotationIndex = glGetUniformLocation(shaderID, "transform.rotation");
        glUniform1f(rotationIndex, rotation);
        GLint scaleIndex = glGetUniformLocation(shaderID, "transform.pixelSize");
        glUniform2f(scaleIndex, scale.x, scale.y);

        unsigned resolutionIndex = glGetUniformLocation(shaderID, "resolutionMultiplier");
        glUniform2f(resolutionIndex, resX, resY);

        float resolutionRatio = 9.f/16.f;//settings.GetResolutionRatio();
        unsigned resolutionRatioIndex = glGetUniformLocation(shaderID, "resolutionRatio");
        glUniform1f(resolutionRatioIndex, resolutionRatio);

        Math::Vector2f size = spriteRectMax - spriteRectMin;

        GLint spriteRectIndex = glGetUniformLocation(shaderID, "material.spriteRect");
        glUniform4f(spriteRectIndex, spriteRectMin.x, spriteRectMin.y, size.x, size.y);

        myMaterial->Use();
        mySprite->Render();

        DebugInformationCollector::UpdateRenderCalls();
    }
}