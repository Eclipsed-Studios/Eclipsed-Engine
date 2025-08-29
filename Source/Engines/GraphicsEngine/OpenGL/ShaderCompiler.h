#include "glad/glad.h"

namespace ENGINE_NAMESPACE
{
    enum class ShaderType
    {
        FRAGMENT_SHADER = 0x8B30,
        VERTEX_SHADER = 0x8B31,
        GEOMETRY_SHADER = 0x8DD9
    };

    class ShaderCompiler
    {
    public:
        static void CompileShaderFromMemory(const char *aShaderSource, unsigned &aShaderID, ShaderType aShaderType);
        static void CompileShaderFromFile(const char *aShaderPath, unsigned &aShaderID, ShaderType aShaderType);
    };
}