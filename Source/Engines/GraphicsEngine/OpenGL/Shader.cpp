#include "Shader.h"

#include "glad/glad.h"
#include "ShaderCompiler.h"

namespace ENGINE_NAMESPACE
{
    int Shader::Init()
    {
        ShaderCompiler::CompileShaderFromFile(ASSET_PATH"Shaders/DefaultSpriteVertexShader.glsl", myVertexShader, ShaderType::VERTEX_SHADER);
        ShaderCompiler::CompileShaderFromFile(ASSET_PATH"Shaders/DefaultSpritePixelShader.glsl", myFragmentShader, ShaderType::FRAGMENT_SHADER);

        myShaderProgram = glCreateProgram();
        glAttachShader(myShaderProgram, myVertexShader);
        glAttachShader(myShaderProgram, myFragmentShader);
        glLinkProgram(myShaderProgram);

        return 0;
    }

    void Shader::Use()
    {
        glUseProgram(myShaderProgram);
    }
}