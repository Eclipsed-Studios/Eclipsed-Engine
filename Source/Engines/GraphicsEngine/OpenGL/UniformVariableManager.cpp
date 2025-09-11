#include "UniformVariableManager.h"

#include "glad/glad.h"

namespace Eclipse
{
    void UniformVariableManager::SetGlobalUniforms(unsigned aShaderProgram)
    {
        glUseProgram(aShaderProgram);

        for (const auto& [uniformName, value] : myGlobalUniformsInt)
        {
            GLuint location = glGetUniformLocation(aShaderProgram, uniformName.c_str());
            glUniform1i(location, value.value);
        }

        for (const auto& [uniformName, value] : myGlobalUniformsFloat)
        {
            GLuint location = glGetUniformLocation(aShaderProgram, uniformName.c_str());
            glUniform1f(location, value.value);
        }

        for (const auto& [uniformName, value] : myGlobalUniformsVector2Float)
        {
            GLuint location = glGetUniformLocation(aShaderProgram, uniformName.c_str());
            glUniform2f(location, value.value.x, value.value.y);
        }
        for (const auto& [uniformName, value] : myGlobalUniformsVector3Float)
        {
            GLuint location = glGetUniformLocation(aShaderProgram, uniformName.c_str());
            glUniform3f(location, value.value.x, value.value.y, value.value.z);
        }
        for (const auto& [uniformName, value] : myGlobalUniformsVector4Float)
        {
            GLuint location = glGetUniformLocation(aShaderProgram, uniformName.c_str());
            glUniform4f(location, value.value.x, value.value.y, value.value.z, value.value.w);
        }

        for (const auto& [uniformName, value] : myGlobalUniformsMatrix2x2Float)
        {
            GLuint location = glGetUniformLocation(aShaderProgram, uniformName.c_str());
            glUniformMatrix2fv(location, 4, GL_FALSE, value.value);
        }
        for (const auto& [uniformName, value] : myGlobalUniformsMatrix3x3Float)
        {
            GLuint location = glGetUniformLocation(aShaderProgram, uniformName.c_str());
            glUniformMatrix3fv(location, 9, GL_FALSE, value.value);
        }
        for (const auto& [uniformName, value] : myGlobalUniformsMatrix4x4Float)
        {
            GLuint location = glGetUniformLocation(aShaderProgram, uniformName.c_str());
            glUniformMatrix4fv(location, 16, GL_FALSE, value.value);
        }
    }
}