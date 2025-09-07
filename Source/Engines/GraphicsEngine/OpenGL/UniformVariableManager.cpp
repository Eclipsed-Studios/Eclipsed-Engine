#include "UniformVariableManager.h"

#include "glad/glad.h"

namespace ENGINE_NAMESPACE
{
    void UniformVariableManager::SetGlobalUniforms(unsigned aShaderProgram)
    {
        glUseProgram(aShaderProgram);

        for (const GlobalUniformValueInt& valueInt : myGlobalUniformsInt)
        {
            GLuint location = glGetUniformLocation(aShaderProgram, valueInt.uniformName.c_str());
            glUniform1i(location, valueInt.value);
        }

        for (const GlobalUniformValueFloat& valueFloat : myGlobalUniformsFloat)
        {
            GLuint location = glGetUniformLocation(aShaderProgram, valueFloat.uniformName.c_str());
            glUniform1f(location, valueFloat.value);
        }

        for (const GlobalUniformValueVector2Float& valueVec2 : myGlobalUniformsVector2Float)
        {
            GLuint location = glGetUniformLocation(aShaderProgram, valueVec2.uniformName.c_str());
            glUniform2f(location, valueVec2.value.x, valueVec2.value.y);
        }
        for (const GlobalUniformValueVector3Float& valueVec3 : myGlobalUniformsVector3Float)
        {
            GLuint location = glGetUniformLocation(aShaderProgram, valueVec3.uniformName.c_str());
            glUniform3f(location, valueVec3.value.x, valueVec3.value.y, valueVec3.value.z);
        }
        for (const GlobalUniformValueVector4Float& valueVec4 : myGlobalUniformsVector4Float)
        {
            GLuint location = glGetUniformLocation(aShaderProgram, valueVec4.uniformName.c_str());
            glUniform4f(location, valueVec4.value.x, valueVec4.value.y, valueVec4.value.z, valueVec4.value.w);
        }

        for (const GlobalUniformValueMatrixMatrix2x2Float& valueMat2 : myGlobalUniformsMatrix2x2Float)
        {
            GLuint location = glGetUniformLocation(aShaderProgram, valueMat2.uniformName.c_str());
            glUniformMatrix2fv(location, 4, GL_FALSE, valueMat2.value);
        }
        for (const GlobalUniformValueMatrixMatrix3x3Float& valueMat3 : myGlobalUniformsMatrix3x3Float)
        {
            GLuint location = glGetUniformLocation(aShaderProgram, valueMat3.uniformName.c_str());
            glUniformMatrix3fv(location, 9, GL_FALSE, valueMat3.value);
        }
        for (const GlobalUniformValueMatrixMatrix4x4Float& valueMat4 : myGlobalUniformsMatrix4x4Float)
        {
            GLuint location = glGetUniformLocation(aShaderProgram, valueMat4.uniformName.c_str());
            glUniformMatrix4fv(location, 16, GL_FALSE, valueMat4.value);
        }
    }
}