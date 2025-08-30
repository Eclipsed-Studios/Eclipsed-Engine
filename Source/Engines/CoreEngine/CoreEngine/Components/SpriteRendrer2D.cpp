#include "SpriteRendrer2D.h"

#include "Transform2D.h"

#include "Math/Vector/Vector2.h"

#include "AssetManagement/Resources/Shaders/Shader.h"
#include "Sprite.h"

#include "../ECS/ComponentManager.h"

// Temporary dont use setuniforms
#include "glad/glad.h"
#include "TemporarySettingsSingleton.h"

namespace ENGINE_NAMESPACE
{
    void Material::SetTexture()
    {
        unsigned shaderID = myShader->GetProgramID();

        GLint diffuseIndex = glGetUniformLocation(shaderID, "material.albedo");
        glUniform1i(shaderID, 0)
    }

    void Material::Use()
    {
        glUseProgram(myShader->GetProgramID());

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, myTextureID);
    }

    void SpriteRendrer2D::Awake()
    {
        mySprite = new Sprite();
        mySprite->Init();

        myShader = new Shader();
        myShader->Create(ASSET_PATH "Shaders/DefaultSpritePixelShader.glsl", ASSET_PATH "Shaders/DefaultSpriteVertexShader.glsl");
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

        GLint positionIndex = glGetUniformLocation(myShader->GetProgramID(), "transform.position");
        glUniform2f(positionIndex, position.x, position.y);
        GLint rotationIndex = glGetUniformLocation(myShader->GetProgramID(), "transform.rotation");
        glUniform1f(rotationIndex, rotation);
        GLint scaleIndex = glGetUniformLocation(myShader->GetProgramID(), "transform.pixelSize");
        glUniform2f(scaleIndex, 100.f * scale.x, 100.f * scale.y);

        auto &settings = TemporarySettingsSingleton::Get();

        float resX = settings.GetResolutionX();
        float resY = settings.GetResolutionY();

        unsigned resolutionIndex = glGetUniformLocation(myShader->GetProgramID(), "resolutionMultiplier");
        glUniform2f(resolutionIndex, 1.f / resX, 1.f / resY);

        myShader->Use();
        mySprite->Render();
    }
}