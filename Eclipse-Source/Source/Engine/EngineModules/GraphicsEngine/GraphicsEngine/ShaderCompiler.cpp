#include "ShaderCompiler.h"

#include <iostream>
#include <vector>

#include <rapidjson/rapidjson/rapidjson.h>
#include <rapidjson/rapidjson/Document.h>
#include "rapidjson/rapidjson/filereadstream.h"

#include <fstream>
#include <filesystem>

namespace Eclipse
{
    void ShaderCompiler::CompileShaderFromMemory(const char *aShaderSource, unsigned &aShaderID, ShaderType aShaderType)
    {
        aShaderID = glCreateShader(static_cast<int>(aShaderType));
        glShaderSource(aShaderID, 1, &aShaderSource, NULL);
        glCompileShader(aShaderID);

        GLint success;
        glGetShaderiv(aShaderID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLint logLength = 0;
            glGetShaderiv(aShaderID, GL_INFO_LOG_LENGTH, &logLength);

            std::vector<char> log(logLength);
            glGetShaderInfoLog(aShaderID, logLength, nullptr, log.data());

            switch (aShaderType)
            {
            case ShaderType::VERTEX_SHADER:
                std::cerr << "Vertex";
                break;
            case ShaderType::FRAGMENT_SHADER:
                std::cerr << "Fragment/Pixel";
                break;
            case ShaderType::GEOMETRY_SHADER:
                std::cerr << "Geometry";
                break;
            }

            std::cerr << " shader compilation failed:\n"
                      << log.data() << std::endl;

            throw("Vertex shader compilation failed");
        }
    }

    void ShaderCompiler::CompileShaderFromFile(const char *aShaderPath, unsigned &aShaderID, ShaderType aShaderType)
    {
        const int fileSize = std::filesystem::file_size(std::filesystem::path(aShaderPath));

        FILE *fileP = fopen(aShaderPath, "rb");
        char readBuffer[4000];
        fread(readBuffer, 1, fileSize, fileP);
        fclose(fileP);
        readBuffer[fileSize] = '\0';

        CompileShaderFromMemory(readBuffer, aShaderID, aShaderType);
    }
}