#include "SpriteRendrer2D.h"

#include "Sprite.h"
#include "AssetManagement/Resources/Shaders/Shader.h"


#include "TemporarySettingsSingleton.h"

// Temporary dont use setuniforms
#include "glad/glad.h"

namespace ENGINE_NAMESPACE
{
    void SpriteRendrer2D::Awake()
    {
        mySprite = new Sprite();
        mySprite->Init();

        myShader = new Shader();
        myShader->Create(ASSET_PATH "Shaders/DefaultSpritePixelShader.glsl", ASSET_PATH "Shaders/DefaultSpriteVertexShader.glsl");
    }

    void SpriteRendrer2D::LateUpdate()
    {
        GLint positionIndex = glGetUniformLocation(myShader->GetProgramID(), "transform.pixelSize");
        glUniform2f(positionIndex, 100, 100);

        auto& settings = TemporarySettingsSingleton::Get();

        float resX = settings.GetResolutionX();
        float resY = settings.GetResolutionY();

        positionIndex = glGetUniformLocation(myShader->GetProgramID(), "resolutionMultiplier");
        glUniform2f(positionIndex, 1.f / resX, 1.f / resY);

        myShader->Use();
        mySprite->Render();
    }
}