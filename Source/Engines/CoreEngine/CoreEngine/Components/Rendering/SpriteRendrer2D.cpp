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

namespace ENGINE_NAMESPACE
{
    Material::Material()
    {
        myShader = new Shader();
        myShader->Create(ASSET_PATH "Shaders/DefaultSpritePixelShader.glsl", ASSET_PATH "Shaders/DefaultSpriteVertexShader.glsl");
    }

    void Material::SetTexture(const char *aPath)
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
        glUniform4f(albedoColorIndex, color.myR, color.myG, color.myB, color.myA);
    }

    void SpriteRendrer2D::SetMaterial(Material *aMaterial)
    {
        myMaterial = aMaterial;
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
        Math::Vector2f position = myTransform->GetPosition();
        float rotation = myTransform->GetRotation();
        Math::Vector2f scale = myTransform->GetScale();

        GLint positionIndex = glGetUniformLocation(myMaterial->myShader->GetProgramID(), "transform.position");
        glUniform2f(positionIndex, position.x, position.y);
        GLint rotationIndex = glGetUniformLocation(myMaterial->myShader->GetProgramID(), "transform.rotation");
        glUniform1f(rotationIndex, rotation);
        GLint scaleIndex = glGetUniformLocation(myMaterial->myShader->GetProgramID(), "transform.pixelSize");
        glUniform2f(scaleIndex, scale.x, scale.y);

        auto &settings = TemporarySettingsSingleton::Get();

        float resX = settings.GetOneDivResolutionX();
        float resY = settings.GetOneDivResolutionY();
        
        unsigned resolutionIndex = glGetUniformLocation(myMaterial->myShader->GetProgramID(), "resolutionMultiplier");
        glUniform2f(resolutionIndex, resX, resY);
        
        float resolutionRatio = settings.GetResolutionRatio();
        unsigned resolutionRatioIndex = glGetUniformLocation(myMaterial->myShader->GetProgramID(), "resolutionRatio");
        glUniform1f(resolutionRatioIndex, resolutionRatio);

        myMaterial->Use();
        mySprite->Render();
    }
}