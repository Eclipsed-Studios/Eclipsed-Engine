#include "ShaderCompiler.h"

#include <iostream>
#include <vector>

#include <rapidjson/rapidjson/rapidjson.h>
#include <rapidjson/rapidjson/Document.h>
#include "rapidjson/rapidjson/filereadstream.h"

#include <fstream>


namespace ENGINE_NAMESPACE
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
        FILE *fileP = fopen(aShaderPath, "rb");
        char readBuffer[2048];
        rapidjson::FileReadStream fileReadStream(fileP, readBuffer, sizeof(readBuffer));

        rapidjson::Document doc;
        doc.ParseStream(fileReadStream);
        fclose(fileP);

        CompileShaderFromMemory(readBuffer, aShaderID, aShaderType);
    }
}