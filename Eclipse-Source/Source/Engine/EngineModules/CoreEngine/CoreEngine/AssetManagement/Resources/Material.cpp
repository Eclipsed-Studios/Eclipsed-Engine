#include "Material.h"

#include "OpenGL/glad/glad.h"

namespace Eclipse
{
    Material::Material(const char* myPixelShader, const char* myVertexShader)
    {
        myShader = new Shader();
        myShader->Create(myPixelShader, myVertexShader);

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
}